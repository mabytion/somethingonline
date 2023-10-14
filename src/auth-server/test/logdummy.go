package main

import (
	"time"
	"io"
	"log"
	"net"
	"strings"
       )

type Logdata struct {
	Date_time	string
	Server		string
	Category	string
	Id		string
	Data		string
}

func main() {
	/* Passive Socket Open */
	listen, err := net.Listen("tcp", ":4001")
	
	if nil != err {
		log.Println(err);
	}
	defer listen.Close()

	for {
		conn, err := listen.Accept()

		if nil != err {
			log.Println(err)
			continue
		}
		defer conn.Close()
		go ConnHandler(conn)
	}
}

func ConnHandler(conn net.Conn) {
	recv := make([]byte, 1526)
	var sdata chan []string = make(chan []string)
	var bdata chan []byte = make(chan []byte)
	
	go MsgHandler(bdata, sdata)
	go Logger(sdata)

	for {
		recv_n, err := conn.Read(recv)
		if nil != err {
			if io.EOF == err {
				log.Println(DatetimeNow(), err);
				return
			}

			log.Println(err);
			return
		}

		if 0 < recv_n {
			bdata <- recv[:recv_n]
			time.Sleep(10 * time.Millisecond)
		}
	}
}

func MsgHandler(bdata chan []byte, sdata chan []string) {
	for {
		str := <-bdata
		data := string(str[:]);
		slice := strings.Split(data, "/")
	
		if(slice[0] == "0") {
			sdata <- slice;
		}
	}

}

func Logger(slice chan []string) {

	for {
		str := <-slice
		newLogdata := Logdata{
			Date_time: DatetimeNow(),
			Server: str[1],
			Category: str[2],
			Id: str[3],
			Data: str[4],
		}

		log.Println(newLogdata)
	}
}

func DatetimeNow() string {
	dt := time.Now()

	return dt.Format("2006-01-02T15:04:05Z")
}
