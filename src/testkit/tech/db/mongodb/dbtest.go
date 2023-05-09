package main

import (
		"context"
		"log"
		"time"
		"os"

		"github.com/joho/godotenv"
		"go.mongodb.org/mongo-driver/mongo"
		"go.mongodb.org/mongo-driver/mongo/options"
       )


type Logdata struct {
	Date_time	string
	Server		string
	Category	string
	Id		string
	Data		strig
}

func main() {
	if err := godotenv.Load(); err != nil {
		log.Println("No .env file found")
	}
	
	uri := os.Getenv("MONGODB_URI")
	
	if uri == "" {
		log.Fatal("You must set your 'MONGODB_URI' environmental variable.")
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

	dt := time.Now()
	log.Println(dt)

	coll := client.Database("log").Collection("log")
	newLogdata := Logdata{
				Date_time: dt.Format("2006-01-02T15:04:05Z"),
				Server: "test",
				Category: "test",
				Id: "test",
				Data: "test",
			     }

	log.Println(newLogdata);
	result, err := coll.InsertOne(context.TODO(), newLogdata)
	if err != nil {
		panic(err)
	}
	log.Println(result);


}

