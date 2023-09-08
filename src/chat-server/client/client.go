package main

import(
		"bytes"
		"encoding/json"
		"io/ioutil"
		"net"
		"net/http"
		"fmt"

		"auth/models"
	  )

func main() {
	var token models.JToken
	var id, pw string

	fmt.Print("ID: ")
	fmt.Scanln(&id)
	fmt.Print("PW: ")
	fmt.Scanln(&pw)

	user := models.User{id, pw}
	ubytes, _ := json.Marshal(user)
	req := bytes.NewBuffer(ubytes)
	res, err := http.Post("http://192.168.75.14:8081/auth/login", "application/json", req)

	resBody, err := ioutil.ReadAll(res.Body)
	if err == nil {
		json.Unmarshal(resBody, &token)
	}

	client(token.Token)
}

func client(token string) {
	c, err := net.Dial("tcp", "192.168.75.12:8082")
	if err != nil {
		fmt.Println(err)
	}

	_, err = c.Write([]byte(token))
	if err != nil {
		fmt.Println(err)
	}

	go msgListener(c)

	for {
		var s string
		fmt.Scanln(&s)
		c.Write([]byte(s))
	}
	
	c.Close()
}

func msgListener(c net.Conn) {
	recv := make([]byte, 4096)

	for
	{
		n, err := c.Read(recv)
		if err != nil {
			fmt.Println(err)
			break
		} else {
			fmt.Println(string(recv[:n]))
		}
	}

}
