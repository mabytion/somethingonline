package timenow

import (
	"time"
	"strconv"
       )

const (
	MONGO = 0
	UNIX = 1
	UNIX30 = 2
      )

func DatetimeNow(mode int) string {
	dt := time.Now()

	switch mode {
		case MONGO:
			return dt.Format("2006-01-02T15:04:05Z")
		case UNIX:
			return strconv.FormatInt(dt.Unix(), 10)
		case UNIX30:
			return strconv.FormatInt(dt.Add(time.Minute * 30).Unix(), 10)
	}

	return "err"

}
