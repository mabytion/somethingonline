package main

import (
	"database/sql"
	"log"

	"github.com/go-gorp/gorp"
	_ "github.com/go-sql-driver/mysql"
       )

var dbmap = initDB()

func main() {

	log.Println(dbmap)

}

func initDB() *gorp.DbMap {
	db, err := sql.Open("mysql","auth:nasnag@/userdb")
	checkErr(err, "fail")

	dbmap := &gorp.DbMap{ Db: db, Dialect: gorp.MySQLDialect{"InnoDB", "UTF8"} }
	err = dbmap.CreateTablesIfNotExists()
	checkErr(err, "faileddd")

	return dbmap

}

func checkErr(err error, msg string) {
	if err != nil {
		log.Fatalln(msg, err)
	}
}
