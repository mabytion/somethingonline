package main

import(
		"bytes"
		"encoding/json"
		"io/ioutil"
		"net"
		"net/http"
		"fmt"
		"bufio"
		"os"

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
	res, err := http.Post("http://192.168.75.15:8081/auth/login", "application/json", req)

	resBody, err := ioutil.ReadAll(res.Body)
	if err == nil {
		json.Unmarshal(resBody, &token)
		fmt.Println(token.Token)
	}

	client(token.Token)
}

func client(token string) {
	c, err := net.Dial("tcp", "127.0.0.1:8082")
	if err != nil {
		fmt.Println(err)
	}

	_, err = c.Write([]byte(token))
	if err != nil {
		fmt.Println(err)
	}

	msgListener(c)

	for {
		reader := bufio.NewReader(os.Stdin)
		fmt.Print("> ")
		text, err := reader.ReadString('\n')
		if err != nil {
			fmt.Print("input err")
		}
		
		fmt.Fprintf(c, "%s", text)
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
