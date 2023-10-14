package main

import (
		"fmt"
		"log"
		"os"
		"os/exec"
		"syscall"
		"time"
	   )

var pipeName = "pipe"

func main() {
	os.Remove(pipeName)
	err := syscall.Mkfifo(pipeName, 0666)
	if err != nil {
		log.Fatal("pipe create err: ", err)
	}

	go msgReader()

	fmt.Println("open pipe for write")
	file, err := os.OpenFile(pipeName, os.O_RDWR|os.O_CREATE|os.O_APPEND, 0777)
	if err != nil {
		log.Fatal("open pipe err: ", err)
	}

	i := 0
	for {
		fmt.Println("write pipe")
		file.WriteString(fmt.Sprintf("0/test1/test2/test3/%d", i))
		i++
		time.Sleep(time.Second)
	}


}

func msgReader() {
	fmt.Println("reader loading...")

	cmd := exec.Command("./loggerdummy")
	fmt.Println("loggerdummy loaded.")
	cmd.Stdout = os.Stdout

	if err := cmd.Run(); err != nil {
	    fmt.Println(err)
	}
}
