function cambioEstadoPrograma(name, checked)
{
	var xhttp = new XMLHttpRequest();
 
  let estadoPrograma = {
     programa: name,
     estado: checked
  }
  console.log(estadoPrograma);
  let datos = JSON.stringify(estadoPrograma);
 
  xhttp.addEventListener('load', function(event) {
    console.log('OK', xhttp);
  });
 
  xhttp.addEventListener('error', function(event) {
    console.log('error', xhttp);
  });
 
  xhttp.open('POST', 'cambioEstadoPrograma');
  xhttp.setRequestHeader('Content-Type', 'application/json');
  xhttp.send(datos);
}

function enviarDatos(name, status)
{
  var xhttp = new XMLHttpRequest();
 
  let datosDispositivo = {
     dispositivo: name,
     estado: status
  }
  let datos = JSON.stringify(datosDispositivo);
 
  xhttp.addEventListener('load', function(event) {
    console.log('OK', xhttp);
  });
 
  xhttp.addEventListener('error', function(event) {
    console.log('error', xhttp);
  });
 
  xhttp.open('POST', 'enviarDatos');
  xhttp.setRequestHeader('Content-Type', 'application/json');
  xhttp.send(datos);
} 

function recibirDatos()
{
    var xhttp = new XMLHttpRequest();
 
    xhttp.onreadystatechange = function() {
        if (xhttp.readyState == XMLHttpRequest.DONE) {
           if (xhttp.status == 200) {
			   console.log((xhttp.responseText));
			   let json = JSON.parse(xhttp.responseText);
				  console.log();
			   
			   document.getElementById('dia').textContent = json.dia;
			   document.getElementById('mes').textContent = json.mes;
			   document.getElementById('ano').textContent = json.ano;
			   document.getElementById('hora').textContent = json.hora;
			   document.getElementById('minuto').textContent = json.minuto;
			   document.getElementById('segundo').textContent = json.segundo;
			   document.getElementById('p1l').textContent = json.programa1.lunes;
			   document.getElementById('p1m').textContent = json.programa1.martes;
			   document.getElementById('p1x').textContent = json.programa1.miercoles;
			   document.getElementById('p1j').textContent = json.programa1.jueves;
			   document.getElementById('p1v').textContent = json.programa1.viernes;
			   document.getElementById('p1s').textContent = json.programa1.sabado;
			   document.getElementById('p1d').textContent = json.programa1.domingo;
			   document.getElementById('p1horaArranque').textContent = json.programa1.horaArranque;
			   document.getElementById('p1horaParada').textContent = json.programa1.horaParada;
			   document.getElementById('p2l').textContent = json.programa2.lunes;
			   document.getElementById('p2m').textContent = json.programa2.martes;
			   document.getElementById('p2x').textContent = json.programa2.miercoles;
			   document.getElementById('p2j').textContent = json.programa2.jueves;
			   document.getElementById('p2v').textContent = json.programa2.viernes;
			   document.getElementById('p2s').textContent = json.programa2.sabado;
			   document.getElementById('p2d').textContent = json.programa2.domingo;
			   document.getElementById('p2horaArranque').textContent = json.programa2.horaArranque;
			   document.getElementById('p2horaParada').textContent = json.programa2.horaParada;
			   document.getElementById('p3l').textContent = json.programa3.lunes;
			   document.getElementById('p3m').textContent = json.programa3.martes;
			   document.getElementById('p3x').textContent = json.programa3.miercoles;
			   document.getElementById('p3j').textContent = json.programa3.jueves;
			   document.getElementById('p3v').textContent = json.programa3.viernes;
			   document.getElementById('p3s').textContent = json.programa3.sabado;
			   document.getElementById('p3d').textContent = json.programa3.domingo;
			   document.getElementById('p3horaArranque').textContent = json.programa3.horaArranque;
			   document.getElementById('p3horaParada').textContent = json.programa3.horaParada;
			   document.getElementById('p4l').textContent = json.programa4.lunes;
			   document.getElementById('p4m').textContent = json.programa4.martes;
			   document.getElementById('p4x').textContent = json.programa4.miercoles;
			   document.getElementById('p4j').textContent = json.programa4.jueves;
			   document.getElementById('p4v').textContent = json.programa4.viernes;
			   document.getElementById('p4s').textContent = json.programa4.sabado;
			   document.getElementById('p4d').textContent = json.programa4.domingo;
			   document.getElementById('p4horaArranque').textContent = json.programa4.horaArranque;
			   document.getElementById('p4horaParada').textContent = json.programa4.horaParada;
			   
			   if ( json.programa1.estadoDepuradora === true)
			   {
					document.getElementById('input-label-p1').textContent = 'ON';
					document.getElementById('input-label-p1').classList.add('On-style');
					document.getElementById('input-label-p1').classList.remove('Off-style');
			   }
				else
				{
					document.getElementById('input-label-p1').textContent = 'OFF';
					document.getElementById('input-label-p1').classList.add('Off-style');
					document.getElementById('input-label-p1').classList.remove('On-style');
				}
				if ( json.programa2.estadoDepuradora === true)
			   {
					document.getElementById('input-label-p2').textContent = 'ON';
					document.getElementById('input-label-p2').classList.add('On-style');
					document.getElementById('input-label-p2').classList.remove('Off-style');
			   }
				else
				{
					document.getElementById('input-label-p2').textContent = 'OFF';
					document.getElementById('input-label-p2').classList.add('Off-style');
					document.getElementById('input-label-p2').classList.remove('On-style');
				}
				if ( json.programa3.estadoDepuradora === true)
			   {
					document.getElementById('input-label-p3').textContent = 'ON';
					document.getElementById('input-label-p3').classList.add('On-style');
					document.getElementById('input-label-p3').classList.remove('Off-style');
			   }
				else
				{
					document.getElementById('input-label-p3').textContent = 'OFF';
					document.getElementById('input-label-p3').classList.add('Off-style');
					document.getElementById('input-label-p3').classList.remove('On-style');
				}
				if ( json.programa4.estadoDepuradora === true)
			   {
					document.getElementById('input-label-p4').textContent = 'ON';
					document.getElementById('input-label-p4').classList.add('On-style');
					document.getElementById('input-label-p4').classList.remove('Off-style');
			   }
				else
				{
					document.getElementById('input-label-p4').textContent = 'OFF';
					document.getElementById('input-label-p4').classList.add('Off-style');
					document.getElementById('input-label-p4').classList.remove('On-style');
				}
				if ( json.programa1.estadoPrograma === true)
					document.getElementById("checkboxProg1").checked = true;
				else
					document.getElementById("checkboxProg1").checked = false;
				if ( json.programa2.estadoPrograma === true)
					document.getElementById("checkboxProg2").checked = true;
				else
					document.getElementById("checkboxProg2").checked = false;
				if ( json.programa3.estadoPrograma === true)
					document.getElementById("checkboxProg3").checked = true;
				else
					document.getElementById("checkboxProg3").checked = false;
				if ( json.programa4.estadoPrograma === true)
					document.getElementById("checkboxProg4").checked = true;
				else
					document.getElementById("checkboxProg4").checked = false;
			}
           else {
              console.log('error', xhttp);
           }
        }
    };
 
    xhttp.open("GET", "recibirDatos", true);
    xhttp.send();
}
(function scheduleAjax() {
    recibirDatos();
    setTimeout(scheduleAjax, 1000);
})();