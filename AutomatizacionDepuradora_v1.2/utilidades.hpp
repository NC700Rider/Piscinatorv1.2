String horaFormatoReloj(uint8_t horas, uint8_t minutos)
{
   String reloj = "";
   if ( horas <= 9 )
    reloj.concat( "0" );
   reloj.concat( horas );
   reloj.concat( ":" );
   if ( minutos <= 9 )
    reloj.concat( "0" );
   reloj.concat( minutos );
   return reloj;
}

String int2Digits(uint8_t entrada)
{
  String digits = "";
   if ( entrada <= 9 )
    digits.concat( "0" );
   digits.concat( entrada );
   return digits;
}
