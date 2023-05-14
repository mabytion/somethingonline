package main

import (
	"fmt"
	"database/sql"
	_ "github.com/go-sql-driver/mysql"
	"crypto/sha256"
	"encoding/hex"
       )

func main() {
	db, _ := sql.Open("mysql", "auth:nasang@/userdb")
	defer db.Close()
	fmt.Print("dbinit() >>> ")
	fmt.Println(db)

	var version string
	db.QueryRow("SELECT VERSION()").Scan(&version)
	fmt.Println("Connected to:", version)

	var name string
	db.QueryRow("select passwd from user where id='test'").Scan(&name)
	fmt.Println("name: " + name)

	h := sha256.New()
	data := "password"

	h.Write([]byte(data))
	md := h.Sum(nil)
	mdStr := hex.EncodeToString(md)

	fmt.Println("mdStr >> " + mdStr)

	fmt.Println(mdStr == name)
}
