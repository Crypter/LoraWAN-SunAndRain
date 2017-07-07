
window.onload = function(){
  getdata('GET', 'https://sun-and-rain.data.thethingsnetwork.org/api/v2/devices', )
 };




 function getdata(metod, url, argumenti){
    var rekvest = new XMLHttpRequest()
     if (metod.toUpperCase()=="GET") {

    console.log("GET");
    if ( argumenti && argumenti.length ) var celourl = url+"?"+argumenti;
    else celourl = url;
         rekvest.open(metod, celourl, false);
         rekvest.setRequestHeader("Authorization", "key ttn-account-v2.9I1h3H0cas6uEO-yYpR2Kzf_RJPTsue7a5JNIRIAxuI");
         rekvest.setRequestHeader('Access-Control-Allow-Origin', '*');
         /*rekvest.onreadystatechange = function() {//Call a function when the state changes.
             if(rekvest.readyState == 4 && rekvest.status == 200) {
                 return rekvest.responseText;
             }
         }*/
         rekvest.send(null);
         if (rekvest.status === 200) return rekvest.responseText;
         else return 0;
     }
     if (metod.toUpperCase()=="POST"){
    console.log("POST");
         rekvest.open(metod, url, false);
         rekvest.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
         rekvest.setRequestHeader("Authorization", "key ttn-account-v2.9I1h3H0cas6uEO-yYpR2Kzf_RJPTsue7a5JNIRIAxuI");
         /*rekvest.onreadystatechange = function() {//Call a function when the state changes.
             if(rekvest.readyState == 4 && rekvest.status == 200) {
                 return rekvest.responseText;
             }
         }*/
         rekvest.send(argumenti);
         if (rekvest.status === 200) return rekvest.responseText;
         else return 0;
     }
 }

</script>
