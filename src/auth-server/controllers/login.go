package controllers

import (
	"fmt"
	"log"

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
	id := c.Params.ByName("id")
	log.Println(id);
	var user models.User2
	err := dbmap.SelectOne(&user, "SELECT id FROM user WHERE id=? LIMIT 1", id)

	if err == nil {
		content := &models.User2{
			Id:	user.Id,
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
		WritePipe(fmt.Sprintf("0/auth/signin/%s/success", user.Id))
		c.JSON(200, content)
	} else {
		log.Println(err)
		WritePipe(fmt.Sprintf("0/auth/signin/%s/fail", user.Id))
		c.JSON(404, gin.H{"error":"user not found"})
	}
}

func PostUser(c *gin.Context) {
	var user models.User
	c.Bind(&user)

	if user.Id != "" && user.Passwd != "" && user.Email != "" {
		if insert, _ := dbmap.Exec(`INSERT INTO user (id, passwd, email) VALUES (?, ?, ?)`, user.Id, user.Passwd, user.Email); insert != nil {
				WritePipe(fmt.Sprintf("0/auth/signup/%s/success", user.Id))
				c.JSON(201, gin.H{"message":"signup successful"})
			} else {
			}
		
	} else {
		WritePipe(fmt.Sprintf("0/auth/signup/%s/fail", user.Id))
		c.JSON(404, gin.H{"error":"Fields are empty"})
	}
}

func Health(c *gin.Context) {
	c.JSON(200, gin.H{"message":"alive"})
}
