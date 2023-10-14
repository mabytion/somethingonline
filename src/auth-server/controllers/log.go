package controllers

import (
		"fmt"
		"log"
		"os"
		"os/exec"
		"syscall"
	   )

var pipeName = "pipe"
var Pipe *os.File

func CreateLogger() {
	os.Remove(pipeName)
	err := syscall.Mkfifo(pipeName, 0666)
	if err != nil {
		log.Fatal("pipe create err: ", err)
	}

	go func() {
		fmt.Println("logger loading...")
		cmd := exec.Command("./logger")
		fmt.Println("logger loaded.")
		cmd.Stdout = os.Stdout

		if err := cmd.Run(); err != nil {
			fmt.Println(err)
		}
	}()

	fmt.Println("open writable pipe")
	file, err := os.OpenFile(pipeName, os.O_RDWR|os.O_CREATE|os.O_APPEND, 0777)
	if err != nil {
		log.Fatal("open pipe err: ", err)
	}

	Pipe = file;

}

func WritePipe(msg string) {
	b := make([]byte, 0, 0)
	b = append([]byte(msg), 0x00)
	Pipe.Write(b)
}
