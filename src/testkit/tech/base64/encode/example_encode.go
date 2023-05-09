package main

import (
	"encoding/base64"
	"fmt"
	iu "io/ioutil"
	"os"
	"bytes"
       )

func main() {

	/* READ FILE */
	bs, err := iu.ReadFile("input.txt")
	if err != nil {
		fmt.Println("err: File Read")
		return
	}
	fmt.Println(string(bs))

	/* BASE64 ENCODE */
	strindex := []string{"Header","Payload","Verify",}
	stdenc := make([]string, 3)
	urlenc := make([]string, 3)

	fmt_slice := bytes.Split(bs, []byte("."))
	for index, elements := range fmt_slice {
		fmt.Println(strindex[index]:w + " >> " + string(elements))

		stdenc_t := base64.RawStdEncoding.EncodeToString(bytes.TrimSpace(elements))
		urlenc_t := base64.RawURLEncoding.EncodeToString(bytes.TrimSpace(elements))

		stdenc[index] = stdenc_t
		urlenc[index] = urlenc_t
	}

	/* WRITE FILE */
	file, err := os.Create("output.txt")
	if err != nil {
		fmt.Println("err: File Create")
		return
	}
	defer file.Close()

	for index, _ := range stdenc {
		file.WriteString(strindex[index] + " std: " + stdenc[index] + "\n")
		file.WriteString(strindex[index] + " url: " + urlenc[index] + "\n")
	}


	fmt.Println(stdenc)
	fmt.Println(urlenc)

}
