package main

import (
	"time"
	"fmt"
	"strconv"
       )

const (
	MONGO = 0
	UNIX = 1
)

func main() {
	fmt.Println(DatetimeNow(MONGO))
	fmt.Println(DatetimeNow(UNIX))
}

func DatetimeNow(mode int) string {
	dt := time.Now()

	switch mode {
		case MONGO:
			return dt.Format("2006-01-02T15:04:05Z")
		case UNIX:
			return strconv.FormatInt(dt.Unix(), 10)
	}	

	return "err";
}
