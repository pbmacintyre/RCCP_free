/**
 * Copyright (C) 2019 Paladin Business Solutions
 *
 */ 

function reveal_it() {
	var w = document.getElementById("myClientSecret");
	var x = document.getElementById("myRCPassword");    
    var y = document.getElementById("myGRCSite");    
	
    if (w.type === "password") {
	  w.type = "text";
	} 
//	if (x.type === "password") {
//	  x.type = "text";
//	}
	if (y.type === "password") {
	  y.type = "text";
	}
}

function hide_it() {
	var w = document.getElementById("myClientSecret");
	var x = document.getElementById("myRCPassword");    
    var y = document.getElementById("myGRCSite");    
	
    if (w.type === "text") {	  
	  w.type = "password";
	}
//	if (x.type === "text") {
//	  x.type = "password";
//	}
	if (y.type === "text") {
	  y.type = "password";
	}
}