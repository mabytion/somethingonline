package main

import (
		"fmt"
		"io/ioutil"
		"net/http"
	   )

func main() {

	res, err := http.Get("http://192.168.75.15:8081/auth/health")
	if err != nil {
		panic(err)
	}
	defer res.Body.Close()

	data, err := ioutil.ReadAll(res.Body)
	if err != nil {
		panic(err)
	}

	fmt.Printf("%s\n", string(data))

}


