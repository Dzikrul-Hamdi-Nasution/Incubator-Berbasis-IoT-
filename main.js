var config = {
    apiKey: "AIzaSyBiJrJ6mmcgLJEgRT5Gy8ikxnrvJDe3zYA",
    authDomain: "tetas-telur-otomatis.firebaseapp.com",
    databaseURL: "https://tetas-telur-otomatis-default-rtdb.firebaseio.com",
    projectId: "tetas-telur-otomatis",
    storageBucket: "tetas-telur-otomatis.appspot.com",
    messagingSenderId: "833271575722",
    appId: "1:833271575722:web:9184edb0463fc265b4ccd3",
    measurementId: "G-WN5VBJ0B49"
  };
  firebase.initializeApp(config);
  

  
  $(document).ready(function() {
    
    keruh();
    oxygen();

  });


  
  

  function keruh() {
    var messagesRef = firebase.database().ref("data_suhu");
    messagesRef.on('value', (snapshot) => {
        const data = snapshot.val();
        $("#keruh").val(data);
    });
  }

  function oxygen() {
    var messagesRef = firebase.database().ref("data_lembap");
    messagesRef.on('value', (snapshot) => {
        const data = snapshot.val();
        $("#do").val(data);
    });
  }

  function oke() {
    firebase.auth().signOut();
    }

    
    function update_suhu() {
        suhu_baru = document.getElementById("set_suhu").value;
        firebase.database().ref().update({
            suhu: suhu_baru,
          });
          alert("suhu telah di update");
    
     }

    firebase.auth().onAuthStateChanged(function(user) {
        if (user) {
            // User is signed in.
           
           ///alert("Database telah di Sinkronkan");
        } else {
            // No user is signed in.
           // alert("Silahkan Login Kembali");
            //window.location.replace("index.html")
        }
      });


    







  


