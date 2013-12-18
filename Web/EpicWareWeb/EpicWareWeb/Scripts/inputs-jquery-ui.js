$(document).ready(function () {
    /* 
    para todos os elementos da classe que vamos chamar de "datePicker", 
    será aplicado o "componente" de calendário no formato brasileiro. 
    */
    $(".datePicker").datepicker({ dateFormat: "dd/mm/yy" });
});