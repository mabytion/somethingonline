package main

import (
		"bytes"
		"encoding/json"
		"io/ioutil"
		"net/http"
		"fmt"

		"auth/models"
	   )

func main() {
	var token models.JToken
	user := models.User{"testaccounts1","123123"}
	ubytes, _ := json.Marshal(user)
	req := bytes.NewBuffer(ubytes)
	res, err := http.Post("http://192.168.75.15:8081/auth/login", "application/json", req)

	resBody, err := ioutil.ReadAll(res.Body)
	if err == nil {
		json.Unmarshal(resBody, &token)
		fmt.Println(token.Token)
	}

	


}
