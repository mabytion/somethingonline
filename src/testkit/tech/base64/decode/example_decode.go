package main

import (
	"encoding/base64"
	"os"
	"fmt"
	"strings"
       )

func main() {

	/* READ FILE */
	file, err := os.Open("input.txt")
	if err != nil {
		fmt.Println("err: File Open \"input.txt\"")
		return
	}
	defer file.Close()

	stat, err := file.Stat()
	if err != nil {
		fmt.Println("err: File Stat")
		return
	}

	bs := make([]byte, stat.Size())
	_, err = file.Read(bs)
	if err != nil { 
		fmt.Println("err: File Read")
		return
	}

	input := string(bs)

	fmt_slice := strings.Split(input, ".")

	fmt.Println(input)

	/* BASE64 DECODE */
	strindex := []string{"Header","Payload","Verify",}
	stddec := make([]string, 3)
	urldec := make([]string, 3)

	for index, elements := range fmt_slice {
		fmt.Println(strindex[index] + " >> " + elements)

		stddec_t, _ := base64.RawStdEncoding.DecodeString(elements)
		urldec_t, _ := base64.RawURLEncoding.DecodeString(elements)

		stddec[index] = string(stddec_t)
		urldec[index] = string(urldec_t)

	}

	/* WRITE FILE */
	file, err = os.Create("output.txt")
	if err != nil {
		fmt.Println("err: File Create \"output.txt\"")
		return
	}
	defer file.Close()

	for index, _ := range stddec {
		file.WriteString(strindex[index] + " std: " + stddec[index] + "\n")
		file.WriteString(strindex[index] + " url: " + urldec[index] + "\n")
	}

}
