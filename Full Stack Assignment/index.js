// YOU CAN USE THIS FILE AS REFERENCE FOR SERVER DEVELOPMENT

// Include the express module
const express = require('express');

// Helps in managing user sessions
const session = require('express-session');

// include the mysql module
var mysql = require('mysql');

var fs = require("fs");

// Bcrypt library for comparing password hashes
const bcrypt = require('bcrypt');

// helps in extracting the body portion of an incoming request stream
var bodyparser = require('body-parser');

const url = require('url');

//change back to 9001
const port = 9001; 

var all_categories = ["academic", "industry", "personal"];
var category_dict = {"academic":"0", "industry":"1", "personal":"2"};

// create an express application
const app = express();

var path = require('path');

var xml2js = require('xml2js');

var parser = new xml2js.Parser();

var id = 50;

// apply the body-parser middleware to all incoming requests
app.use(bodyparser());
app.use(bodyparser.json());
app.use(bodyparser.urlencoded());

var dbCon;
fs.readFile(__dirname + '/dbconfig.xml', function(err, data) {
    parser.parseString(data, function (err, result) {
      console.log(result)
        dbCon = mysql.createPool({
          connectionLimit: 1024,
          host: result.dbconfig.host[0],
          user: result.dbconfig.user[0],
          password: result.dbconfig.password[0],
          database: result.dbconfig.database[0],
          port: result.dbconfig.port[0]
        });

        dbCon.getConnection(function(err) {
          if (err) {
          	console.log("error was called from line 59 before connected to SQL database");
            throw err;
          };
          console.log("Connected to MYSQL database!");
        });
    });
});

// const dbCon = mysql.createConnection({
//     host: "localhost",
//     user: "root",               // replace with the database user provided to you
//     password: "275",           // replace with the database password provided to you
//     database: "project",           // replace with the database user provided to you
//     port: 3306
// });

// dbCon.connect(function(err) {
//   if (err) throw err;
//   console.log("Connected to SQL database");
//   dbCon.query("SELECT * FROM tbl_accounts", function (err, result, fields) {
//     if (err) throw err;
//     console.log(result);
//     dbCon.query("SELECT * FROM contact_table", function (err, result, fields) {
//     if (err) throw err;
//     console.log(result);
//   });
//   });
// });

// Use express-session
// In-memory session is sufficient for this assignment
app.use(session({
        secret: "csci4131secretkey",
        saveUninitialized: true,
        resave: false
    }
));

// middle ware to serve static files
app.use('/client', express.static(__dirname + '/client'));

// server listens on port set to value above for incoming connections
app.listen(port, () => console.log('Listening on port', port));

app.use(express.static(path.join(__dirname, 'public')));

//All end-points
app.get('/',function(req, res) {
  res.sendFile(__dirname + '/client/welcome.html');
});

app.get('/login', function(req, res){
	if (req.session.loggedIn){
		res.sendFile(__dirname + '/client/AllContacts.html');
	} else {
		res.sendFile(__dirname + '/client/Login.html');
	}
});

app.get('/welcome', function(req, res){
	res.sendFile(__dirname + '/client/welcome.html');
});

app.get('/AllContacts', function(req, res){
	if (req.session.loggedIn){
		res.sendFile(__dirname + '/client/AllContacts.html');
	} else {
		res.redirect('/login');
	}
});

app.get('/AddContact', function(req, res){
	if (req.session.loggedIn){
		res.sendFile(__dirname + '/client/AddContact.html');
	} else {
		res.redirect('/login');
	}
});

app.get('/Stocks', function(req, res){
	if (req.session.loggedIn){
		res.sendFile(__dirname + '/client/Stocks.html');
	} else {
		res.redirect('/login');
	}
});

app.get('/Admin', function(req, res){
	if (req.session.loggedIn){
		res.sendFile(__dirname + '/client/Admin.html');
	} else {
		res.redirect('/login');
	}
});

app.post('/logintest', bodyparser(), function(req, res){
	let data = req.body;
	let username = data.username;
	let password = data.password;
	console.log("loginTest was called");
	console.log("The password that was sent was: " + username);
	console.log("The password that was sent was: " + req.body.password);
	console.log("The password that was hashed was: " + password);
	//console.log(username + " " + password);
	//new from here
	//console.log(data);
	dbCon.query(
		'SELECT * FROM tbl_accounts WHERE acc_login = ?', 
		[username], 
		(err, results) => {
			if (err){
				throw err;
			}
			results = JSON.parse(JSON.stringify(results));
			//console.log(results);
			//console.log("comparing " + results[0].acc_password + " with " + password);
			if (results.length >= 1 && bcrypt.compareSync(password, results[0].acc_password)){
				req.session.regenerate((err) => {
					if (err) {
						throw err;
					} else {
						req.session.user = username;
						req.session.loggedIn = true;
						res.json({status: 'success'});
					}
				});
			} else {
				res.json({status: 'failed'});
			}
		});
	//old here
	// if((username=='user' && password=='pass') || (username=='login1' && password=='pass1')){
	// 	console.log("They match");
	// 	req.session.user = username;
	// 	req.session.loggedIn = true;
	// 	res.json({status: 'success'});
	// } else {
	// 	res.json({status: 'failed'});
	// };

	// var loginInfo = req.body;
	// let username = req.body.username;
	// let password = req.body.password;
	// res.json({status: 'success'});
});

app.get('/getContacts', function(req, res) {
	if (req.session.user) {
		var q = url.parse(req.url, true);
		let cat = q.query.category;
		dbCon.query(
	      'SELECT * FROM contact_table WHERE contact_category = ?',
	        [cat],
	      (err, results) => {
	        if (err) {
	          throw err;
	        } else {
	          results = JSON.parse(JSON.stringify(results));

	          // sort by contact names
	          results.sort((a, b) => a.contact_name.localeCompare(b.contact_name));
	          // console.log(results);
	          var data = [];
	          for (var i in results) {
	            data.push({
							category: 	results[i].contact_category,
							name: 		results[i].contact_name,
							location: 	results[i].contact_location,
							info: 		results[i].contact_info,
							email: 		results[i].contact_email,
							title: 		results[i].website_title,
							url: 		results[i].website_url,
						});
	          }
	          //console.log(data);
	          res.json(data);
	        }
	      }
	    )
	} else {
		res.redirect(302, '/login')
	}
});



app.get('/getAllContacts', function(req, res) {
	if (req.session.user) {
		dbCon.query(
			'SELECT * FROM contact_table', 
			(err, results) => {
				if (err) {
					throw err;
				} else {
					results = JSON.parse(JSON.stringify(results));
					for (var i in results) {
						results[i].cat_index = category_dict[results[i].contact_category];
						//console.log(results[i].day_index);
						//console.log(results[i].event_day);
					}
					var data = [];
					for (var i in results) {
						data.push({
							category: 	results[i].contact_category,
							name: 		results[i].contact_name,
							location: 	results[i].contact_location,
							info: 		results[i].contact_info,
							email: 		results[i].contact_email,
							title: 		results[i].website_title,
							url: 		results[i].website_url,
						});
					}
					//console.log("the data array contains: " + data);
				res.json(data);
			}
		}
	)
	} else {
		res.redirect(302, '/login')
	}
});

app.get('/logout',(req,res)=>
{
	req.session.destroy((err)=>{})
	res.sendFile(__dirname + '/client/welcome.html');
});

	
// GET method route for the contacts page.
// It serves MyContacts.html present in client folder
app.get('/MyContacts', function(req, res) {
    // TODO: Add Implementation
    if (req.session.loggedIn){
		res.sendFile(__dirname + '/client/MyContacts.html');
	} else {
		res.redirect('/login');
	}
});

app.post('/postContactEntry', bodyparser(), function(req, res) {
    //console.log("calling function");
    reqBody = req.body;
    updateContacts(req, res, reqBody);
    //console.log("function called and done");
  	// req.on('data', function(data){
  	// 	console.log("made it to first body");
  	// 	reqBody += data;
  	// 	console.log(data);
  	// }); 
  	// req.on('end', function(){
  	// 	console.log("made it to update contacts");
  	// 	updateContacts(req, res, reqBody);
  	// 	console.log("Contact updated");
  	// });
});

function updateContacts(req, res, reqBody){
	console.log(req.body);
	var name = req.body.name;
  	var category = req.body.category;
  	var location = req.body.location;
  	var info = req.body.info;
  	var email = req.body.email;
 	var title = req.body.website_title;
  	var url = req.body.url;
  	// dbCon.connect(function(err) {
  	// console.log("Connected!");
	dbCon.query( 
		'INSERT contact_table SET ?', 
	{
		contact_category: category,
		contact_name: name,
		contact_location: location,
		contact_info: info,
		contact_email: email,
		website_title: title,
		website_url: url
	},
	(err, results) => {
		if (err) {
			throw err;
		} else {
			// console.log("Contact has been inserted");
			dbCon.query("SELECT * FROM contact_table", function (err, result, fields) {
    		// console.log(result);
    		res.redirect(302, '/AllContacts')
  		});
	}
	}
	)
};

// TODO: Add implementation for other necessary end-points

// function to return the 404 message and error to client

app.get('/userLogin', function (req, res) {
	console.log("userLogin was called");
	res.send({login: req.session.user});
});

// new content from here to bottom  
//<---------------------------------------------------------------------------------->
// Get request:  to route :/getListOfUsers (to get list of people with logins) from the accounts table 
// If session id (user) is set 
//  Select query 
//  //Loop through the results obtained from the query and build  
//               // an array of json objects 
//  var objArray = []; 
// for (var i in results){  
//   var obj = {  id: results[i].acc_id, 
//        name: results[i].acc_name, 
//                   login: results[i].acc_login, 
//                  password: results[i].acc_password 
//               }; 
//   objArray.push(obj); 
//  } 
//  res.json(objArray):  
 //<---------------------------------------------------------------------------------->
 app.get('/getListOfUsers', function(req, res) {
	if (req.session.user) {
		dbCon.query(
			'SELECT * FROM tbl_accounts', 
			(err, results) => {
				if (err) {
					throw err;
				} else {
					results = JSON.parse(JSON.stringify(results));
					//console.log("The results are: " + results);
					// for (var i in results) {
					// 	results[i].cat_index = category_dict[results[i].contact_category];
					// 	console.log(results[i].day_index);
					// 	console.log(results[i].event_day);
					// }
					var objArray = [];
					for (var i in results) {
						var obj = {  
						id: results[i].acc_id, 
       					name: results[i].acc_name, 
                  		login: results[i].acc_login, 
                 		password: results[i].acc_password 
              		}; 
					objArray.push(obj); 
					//console.log("the objArray array contains: " + objArray);
				}
				res.json(objArray);
				dbCon.query("SELECT * FROM tbl_accounts", function (err, result, fields) {
    				//console.log("results from line 379 of getListUser" + result);
				});
			}
		}
	)
	} else {
		res.redirect(302, '/login')
	}
});
//<---------------------------------------------------------------------------------->
//Post  request to  route:/addUser  - user login as a parameter (add a user to tbl_accounts)) 
// If session id (user)  is set 
// //req.body.login will contain the login id  
// //check whether the login already exists (select query) 
// if the length (number of rows) returned is zero: 
// insert the name, login and password of the new user into the  tbl_accounts table in your  
// database 
// see the file from Homework 6 – insert into accounts table for an example 
// of how to do this 
//    return a json object in your response 
//    res.send({flag: true, id: result.insertId}); 
 
// else 
//   // the login already exists, send false back in json object to indicate error 
//   res.send({flag:false}); 
// else 
//  redirect to login page 
//<---------------------------------------------------------------------------------->
app.post('/addUser', function(req, res) {
	if (req.session.user) {
		let i = 0;
		let temp = true;
		const password = bcrypt.hashSync(req.body.password, 10);
		dbCon.query (
			'SELECT acc_login FROM tbl_accounts', 
			(err, results) => {
				if (err) {
					throw err;
				} else {
					let test = JSON.parse(JSON.stringify(results)); 
					//console.log(test);
					// console.log(results.length);
					//console.log(results); // [object object]
					for (i = 0; i < results.length; i++) {
						if (test[i].acc_login == req.body.login) {
							temp = false;
							console.log(test[i].acc_login);
							console.log(req.body.login);
						}
					}
					if (temp) {
						id++;
						dbCon.query(
							'INSERT tbl_accounts SET ?', 
							{
								acc_name: req.body.name,
								acc_login: req.body.login,
								acc_password: password,
							}); //end of INSERT query
						console.log("testing: " + req.body.login);
						dbCon.query(
							'SELECT acc_id FROM tbl_accounts WHERE acc_login = ?', 
							[req.body.login],
							(err, results) => {
								console.log(results); 
								res.send({flag:true, id:id}); //could not get ID from SELECT?
						});
					} else 
						res.send({flag:false});
					}
				//res.send({flag:false});
			}); //end of SELECT query
	} else {
		res.redirect(302, '/login')
	}
});

 // <---------------------------------------------------------------------------------->
//Post request to route: /updateUser  (editing/changing info on an existing login) 
//  If session id (user) is set 
//  // check to make sure the the login id exists only for the id associated with the login 
//  // 
//               SELECT * FROM tbl_accounts where acc_login = ? and acc_id != ? 
//               req.body.login should have the login, and req.body.id should have the row id 
//  if result.length == 0 //then login id does not exist for another account 
//   if req.body.password is not null 

//    Update name, login, and password where acc_id  = req.body.id   
//    Makesure to bcrypt.hash( req.body.password) with the proper salt value 
//    (10 is the default value we use....) 
//   Otherwise  
//    Update name, login where accd_id = req.body.id 
 
//   res.send({flag:true}); 
//  else //login already exsits 
//   res.send({flag:false}); 
// else 
 // redirect to login page 
//<---------------------------------------------------------------------------------->
app.post('/updateUser', function(req, res) {
	if (req.session.user) {
		let username = req.body.name;
		let password = bcrypt.hashSync(req.body.password, 10);
		let login = req.body.login;
		let id = req.body.id;
		//console.log("The login sent was: " + req.body.login);
		//console.log("The ID sent was: " + req.body.id);
		dbCon.query(
			'SELECT * FROM tbl_accounts WHERE acc_login = ? and acc_id = ?',
			[login, id],
			(err, results) => {
				if (err) {
					throw err;
				} else {
					//console.log(results);
					if (results.length == 0) { //login does not exist for another account
						//console.log("The results.length did not exist for another account");
						if (req.body.password != null){
							//console.log("calling update function");
							dbCon.query(
								'UPDATE tbl_accounts SET ? WHERE acc_id = ?', 
								[{acc_name: username, acc_login: login, acc_password: password}, id],
								(err, results) => {
									if (err) {
										throw err;
									} else {
										//console.log("update function called, sending true flag");
										res.send({flag:true});
									}
								}
							) //end of UPDATE sql call
							//res.send({flag:true}); this was for testing purposes
						} else {
							res.send({flag:false}); 
						}
					}
				}
			}
		);
	}
	else {
		res.redirect(302, '/login')
	}
});

 // <---------------------------------------------------------------------------------->
//Post request to route: /deleteUser  (delete a user) 
//  If session id (user)  is set 
 
//  If the  req.body.login is not the same as the person who is currently logged in 
//  (when you set your session id upon a successful login, store the login id in a session variable,  
//                 And then compare that value to req.body.login sent by the post request) 
 
//   DELETE FROM tbl_accounts where acc_login = req.body.login 
//   res.send({flag:true}): 
//  else 
//   res.send({flag:false}); 
// else 
 // redirect to login page 
//<---------------------------------------------------------------------------------->
app.post('/deleteUser', function(req, res) {
	if (req.session.user) {
		const login = req.body.login;
		if (req.session.user != login) {
			console.log("They do not match, can delete");
			dbCon.query(
			'DELETE FROM tbl_accounts WHERE acc_login = ?', 
			[login], 
			(err, results) => {
				if (err) {
					throw err;
				} else {
					res.send({flag:true});
				}
			}
		)
		} else {
			console.log("User and login info do not match, cannot delete");
			res.send({flag:false});
		}
	} else {
		res.redirect(302, '/login')
	}
});
//<---------------------------------------------------------------------------------->

app.get('*', function(req, res) {
  // add details
  res.sendStatus(404);
});