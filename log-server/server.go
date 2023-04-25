package main

import (
	"io"
	"log"
	"net"
       )

func main() {
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
	recv := make([]byte, 4096)

	for {
		recv_n, err := conn.Read(recv)
		if nil != err {
			if io.EOF == err {
				log.Println(err);
				return
			}

			log.Println(err);
			return
		}

		if 0 < recv_n {
			data := recv[:recv_n]
			log.Println(string(data))
			_, err = conn.Write(data[:recv_n])
	
			if err != nil {
				log.Println(err)
				return
			}
		}
	}
}

func MsgHandler() {
	
}

func Logger() {

}
