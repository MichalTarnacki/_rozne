
function hide(){
    if(window.localStorage){
  localStorage.setItem("cookies", "allowed");
  document.getElementById("cookies").style.display="none";
}
}
function cookies(){
  if(window.localStorage){
  if(localStorage.getItem("cookies")=="allowed") {
  document.getElementById("cookies").style.display="none";}
  else {  document.getElementById("cookies").style.display="block";}
}
}
function mobilemenu(){
  if(document.getElementById("nav").style.display=='block'){
    document.getElementById("nav").style.display='none';
  }
  else{
    document.getElementById("nav").style.display='block';
  }
}
window.addEventListener("resize", function(){
  if(window.matchMedia("(min-width:760px)").matches){
    document.getElementById("nav").style.display="block";
      document.getElementById("mobile-menu").style.display="none";
  }
  else{ document.getElementById("nav").style.display="none";
  document.getElementById("mobile-menu").style.display="block"
  }
})
window.addEventListener("load", function(){
  if(window.matchMedia("(min-width:760px)").matches){
    document.getElementById("nav").style.display="block";
  }
  else{ document.getElementById("nav").style.display="none"}
})
function user(){
    if(window.sessionStorage){
  let username = document.forms["username"]["INPUTBOX"].value;
  if(username!=0){
  sessionStorage.setItem("user", username );
    window.location.reload();
    return false;
}
}
}
function setuser(){
    if(window.sessionStorage){
  if(sessionStorage.getItem("user")!=null){
      document.getElementById("setuser").style.display="none";
      document.getElementById("main").style.display="block";
  }
  else{
    document.getElementById("setuser").style.display="block";
    document.getElementById("main").style.display="none";
}
}
}
function state(){
  addtitle();
  addtext();
}
function addtitle(){
  if(document.getElementById("checkbox").checked==true){
  if(document.forms["addthread"]["text"].value!=0&&document.forms["addthread"]["title"].value!=0){
  var thread=document.createElement("h1")
  var threadvalue=document.forms["addthread"]["powod"].value + "//T:"+ document.forms["addthread"]["title"].value;
  var threadbox=document.createTextNode(threadvalue);
  thread.appendChild(threadbox);
  document.getElementById("threads").appendChild(thread);
}
}
}
function addtext(){
  if(document.getElementById("checkbox").checked==true){
    if(document.forms["addthread"]["text"].value!=0&&document.forms["addthread"]["title"].value!=0){
  var text=document.createElement("p");
  var textvalue="W:"+ document.forms["addthread"]["text"].value +":/" + sessionStorage.getItem("user");
  var textbox=document.createTextNode(textvalue);
  text.appendChild(textbox);
  document.getElementById("threads").appendChild(text);
}
}
}
function showform(){
  if(document.getElementById("addthread").style.display=="block"){
  document.getElementById("addthread").style.display="none";}
  else{document.getElementById("addthread").style.display="block";}
}
function newcontentshow(){

  document.getElementById("newcontent").style.display="block";
    document.getElementById("nojavascript").style.display="none";
}
function mobilemenushow(){
    if(window.matchMedia("(max-width:759px)").matches){
        document.getElementById("mobile-menu").style.display="block";
      }
}
function resetuser(){
    if(window.sessionStorage){
  sessionStorage.removeItem("user");
  window.location.reload();
}
}
function nocookies(){
    if(window.localStorage&&window.sessionStorage){
  localStorage.clear();
  sessionStorage.clear();
  window.location.href="https://www.google.com";
}
}
function showactiveuser(){
    if(window.localStorage){
  document.getElementById("activeuser").innerHTML = localStorage.getItem("user");
}
}
function timesseen(){
    if(window.localStorage){
  if(localStorage.getItem("timesseen")!=null){
    localStorage.setItem("timesseen",Number(localStorage.getItem("timesseen"))+1);
  }
  else {
    localStorage.setItem("timesseen", 1);
  }
}
}
function showrecipes(){
  if(window.matchMedia("(min-width:999px)").matches){
  document.getElementById("przepisy").style.display="block";
  document.getElementById("constructiondiv").style.display="none"
}
else {
  document.getElementById("przepisy").style.display="none";
    document.getElementById("constructiondiv").style.display="block";
}
}
