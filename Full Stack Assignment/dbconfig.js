var mysql = require("mysql");
var express = require("express");

// fs module - provides an API for interacting with the file system
var fs = require("fs");
var app = express();

// requied for reading XML files
var xml2js = require('xml2js');

var dbcon;

var parser = new xml2js.Parser();
fs.readFile(__dirname + '/dbconfig.xml', function(err, data) {
    parser.parseString(data, function (err, result) {
      console.log(result)
        dbcon = mysql.createConnection({
          host: result.dbconfig.host[0],
          user: result.dbconfig.user[0],
          password: result.dbconfig.password[0],
          database: result.dbconfig.database[0],
          port: result.dbconfig.port[0]
        });

        dbcon.connect(function(err) {
          if (err) {
            throw err;
          };
          console.log("Connected to MYSQL database!");
        });
    });
});