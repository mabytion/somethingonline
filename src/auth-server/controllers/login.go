package controllers

import (
	"log"
	"strconv"

	"auth/models"
	jtk "mabytion/jwt"
	tn "mabytion/timenow"

	"github.com/gin-gonic/gin"
	_ "github.com/go-sql-driver/mysql"
       )

func GetUser(c *gin.Context) {
	var user []models.User
	_, err := dbmap.Select(&user, "select * from user")

	if err == nil {
		c.JSON(200, user)
	} else {
		c.JSON(404, gin.H{"error": "user not found"})
	}
}

func GetUserDetail(c *gin.Context) {
	id := c.Params.ByName("cid")
	var user models.User
	err := dbmap.SelectOne(&user, "SELECT * FROM user WHERE id=? LIMIT 1", id)

	if err == nil {
		user_id, _ := strconv.ParseInt(id, 0, 64)

		content := &models.User{
			Cid:	user_id,
			Id:	user.Id,
			Passwd:	user.Passwd,
			Email:	user.Email,
		}
		c.JSON(200, content)
	} else {
		c.JSON(404, gin.H{"error":"user not found"})
	}
}

func Login(c *gin.Context) {
	var user models.User
	c.Bind(&user)
	inputpwd := user.Passwd;
	err := dbmap.SelectOne(&user, "SELECT * FROM user WHERE id=? LIMIT 1", user.Id)

	if err == nil && inputpwd == user.Passwd {
		jwt_ := jtk.Start()
		jwt_.SetPayload(jwt_.GetPayload(jtk.ISS),
				user.Id,
				"access_token",
				tn.DatetimeNow(tn.UNIX30),
				tn.DatetimeNow(tn.UNIX))

		content := &models.RData {
			Token:	jwt_.CreateTokenString("2JkpyD4C5v_qW=nzKkGCKCG-hhhb6K&2sk+m-72s^ntMXWC3fHUt^b6s7Ksg7DmA"),
		}
		c.JSON(200, content)
	} else {
		log.Println(err)
		c.JSON(404, gin.H{"error":"user not found"})
	}
}

func PostUser(c *gin.Context) {
	var user models.User
	c.Bind(&user)

	if user.Id != "" && user.Passwd != "" && user.Email != "" {
		if insert, _ := dbmap.Exec(`INSERT INTO user (id, passwd, email) VALUES (?, ?, ?)`, user.Id, user.Passwd, user.Email); insert != nil {
				c.JSON(201, gin.H{"message":"signup successful"})
			} else {
			}
		
	} else {
		c.JSON(404, gin.H{"error":"Fields are empty"})
	}
}

func Health(c *gin.Context) {
	c.JSON(200, gin.H{"message":"alive"})
}
