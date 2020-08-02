<?php 
$dbconsulta = new PDO('mysql:host=gualambo.com;dbname=g_mantenimiento;port=3306', 'gualambo', '70kP[PA%,~?T');

$q1 = "select * from keylogger";
$datos = array();

if ($resultInser = $dbconsulta->query($q1)) {
    foreach ($resultInser as $row) {
        $datos[] = $row;
    }
}

$dbconsulta = null;


    echo json_encode(array("respuesta"=>$datos));
?>
