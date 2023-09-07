package controllers

import (
	"database/sql"
	"log"

	"github.com/gin-gonic/gin"
	"github.com/go-gorp/gorp"
	_ "github.com/go-sql-driver/mysql"
       )

var dbmap = initDb()

func initDb() *gorp.DbMap {
	db, err := sql.Open("mysql","auth:nasang@/userdb")

	var version string
	err = db.QueryRow("SELECT VERSION()").Scan(&version)
	log.Println("Connected to:")
	log.Println(version)
	checkErr(err, "sql.Open failed")

	dbmap := &gorp.DbMap{
		Db: db,
		Dialect: gorp.MySQLDialect{"InnoDB", "UTF8"},
	}
	err = dbmap.CreateTablesIfNotExists()
	checkErr(err, "Create tables failed")

	return dbmap
}

func checkErr(err error, msg string) {
	if err != nil {
		log.Fatalln(msg, err)
	}
}

func Cors() gin.HandlerFunc {
	return func(c *gin.Context) {
		c.Writer.Header().Add("Access-Control-Allow-Origin","*")
		c.Next()
	}
}
