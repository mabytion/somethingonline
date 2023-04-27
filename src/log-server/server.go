package main

import (
	"context"
	"time"
	"io"
	"log"
	"net"
	"os"
	"strings"

	"github.com/joho/godotenv"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
       )

type Logdata struct {
	Date_time	string
	Server		string
	Category	string
	Id		string
	Data		string
}

func main() {
	/* DB Init. */

	if err := godotenv.Load(); err != nil {
		log.Println("No .env file found")
	}

	uri := os.Getenv("MONGODB_URI")

	if uri == "" {
		log.Fatal("You must set your 'MONGODB_URI' environment variable.")
	}

	client, err := mongo.Connect(context.TODO(), options.Client().ApplyURI(uri))
	if err != nil {
		panic(err)
	}
	defer func() {
		if err := client.Disconnect(context.TODO()); err != nil {
			panic(err)
		}
	}()

	coll := client.Database("log").Collection("log")

	log.Println("OK.")

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
		go ConnHandler(conn, coll)
	}
}

func ConnHandler(conn net.Conn, coll *mongo.Collection) {
	recv := make([]byte, 4096)
	var sdata chan []string = make(chan []string)
	var bdata chan []byte = make(chan []byte)
	
	go MsgHandler(bdata, sdata)
	go Logger(sdata, coll)

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

func Logger(slice chan []string, coll *mongo.Collection) {

	for {
		dt := time.Now()
		str := <-slice
		newLogdata := Logdata{
			Date_time: dt.Format("2006-01-02T15:04:05Z"),
			Server: str[1],
			Category: str[2],
			Id: str[3],
			Data: str[4],
		}

//		result, err := coll.InsertOne(context.TODO(), newLogdata)
		_, err := coll.InsertOne(context.TODO(), newLogdata)
		if err != nil {
			log.Println(err)
		}

//		log.Println(result)
//		log.Println(newLogdata)
	}
}

func DatetimeNow() string {
	dt := time.Now()

	return dt.Format("2006-01-02T15:04:05Z")
}
