package mappings

import (
	"auth/controllers"
	"github.com/gin-gonic/gin"
       )

var Router *gin.Engine

func CreateUrlMappings() {
	Router = gin.Default()

//	Router.Use(controllers.Cors())
	auth := Router.Group("/auth")
	{
		auth.GET("/health", controllers.Health)
		auth.GET("/getuser/:id", controllers.GetUserDetail)
		auth.POST("/signup", controllers.PostUser)
		auth.POST("/login", controllers.Login)
	}

}
