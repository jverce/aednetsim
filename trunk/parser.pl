#!/usr/bin/perl

use Getopt::Long;
use CGI;


# Tabla hash que se encarga de apuntar
# cada opcion a procesar, hacia una variable, 
# de la forma opcion => opt_opcion.
# Será luego usada por GetOptions del módulo
# Getopt::Long.
%OPTS = (
	"od"	=>	\$opt_od,
	"os"	=>	\$opt_os,
	"ss=s@"	=>	\@opt_ss,
	"sd=s@"	=>	\@opt_sd,
	"t"	=>	\$opt_t,
	"na"	=>	\$opt_na,
	"an"	=>	\$opt_an,
	"sw"	=>	\$opt_sw,
	"si"	=>	\$opt_si,
	"mw"	=>	\$opt_mw,
	"mn"	=>	\$opt_mn,

	"f=s"	=>	\$opt_f,
	"o=s"	=>	\$opt_o
);


# Hash que mapea los meses en forma de
# números a los meses en forma de 
# palabra.
%MONTHS = (
	"01"	=>	"Enero",
	"02"	=>	"Febrero",
	"03"	=>	"Marzo",
	"04"	=>	"Abril",
	"05"	=>	"Mayo",
	"06"	=>	"Junio",
	"07"	=>	"Julio",
	"08"	=>	"Agosto",
	"09"	=>	"Septiembre",
	"10"	=>	"Octubre",
	"11"	=>	"Noviembre",
	"12"	=>	"Diciembre"
);

# Hash que almacena los números en forma
# de palabra, para imprimir de forma más
# clara las notas en el informe de salida.
%GRADES = (
	"0 "	=>	"Cero",
	"1 "	=>	"Uno",
	"2 "	=>	"Dos",
	"3 "	=>	"Tres",
	"4 "	=>	"Cuatro",
	"5 "	=>	"Cinco",
	"6 "	=>	"Seis",
	"7 "	=>	"Siete",
	"8 "	=>	"Ocho",
	"9 "	=>	"Nueve",
	"10 "	=>	"Diez"
);

# Tabla hash que permite obtener el 
# sexo en forma de palabra, con indicar
# la inicial (en minúscula o mayúscula).
%SEX = (
	"m"	=>	"Hombre",
	"M"	=>	"Hombre",

	"f"	=>	"Mujer",
	"F"	=>	"Mujer"
);

# Se guardan las opciones y se las procesa.
@args = @ARGV;
GetOptions(%OPTS);

# Se procesa la opción -f
# que indica el archivo de texto de entrada
# de donde se obtendrá la información.
if ($opt_f)
{
	open(FILE, $opt_f) or
	die "Parser error: por favor, indique un nombre de archivo correcto!";
}
else
{
	open(FILE, "datosalu.txt");	# Nombre de archivo por defecto.
}


# A continuación se procesa el archivo de entrada.
foreach $line (<FILE>)
{	

	# Se debe saber si se va a procesar la 
	# linea que identifica a cada alumno, o 
	# alguna linea de las materias que cada alumno
	# rindio.
	
	$old_1 = $1;
	
	$line =~ m/^(\d+) \/ (\d+)/x;
	if ($old_1 != $1)
	{
		$other = 0;
	}
	else
	{
		$other = 1;
	}
	
	# Este bloque procesa la primer linea para cada
	# alumno (el nombre, la matricula, etc.).

	if ( $other and ($line != "\n") )
	{
		$line =~ m/
			(\d+) (\s+)
			(\w+) (\W) (\s+) (\w+) (\s*) (\w*) (\s+) 
			(\w*) (\s+) (\d.+) (\s+)
			(\d+) (\s+)
			(\w+)/x;
	
		$last_name = uc($3);
		$first_name = uc($6);
		$second_name = uc($8);

		$sex = $16;
		$age = $14;
		$num = $1;

		$person = "$last_name.$first_name.$second_name";
		$people{ $person }{ "SEX" } = uc($sex);
		$people{ $person }{ "AGE" } = $age;
		$people{ $person }{ "NUM" } = $num;
	}

	# En este bloque se procesan las lineas
	# que corresponden a las materias, las notas, etc..

	elsif ($line != "\n")
	{
		$line =~ m/
			(\d+) (\/+) (\d+) (\/+) (\d+) (\s+)
			(\w+) (\s*) (\w*) (\s+)
			(\d+) (\s*) (\w*) (\s+)
			Prof\. (\s+)
			(\w+)/x;

		$year = $5;
		$month = $3;
		$day = $1;
		$date = get_date($year, $month, $day);
			
		$materia = uc($7).".".uc($9);
		$grade = $11;
		$profe = $16;

		$profe =~ m/(\w) (\w*)/x;
		$profe = uc($1).lc($2);

		save_in_people($person, $materia, $grade, $date, $profe);
	}
}

# Cerramos el archivo de entrada.
close(FILE);

start_web_page();

$web_page .= "<b><u>\n\t";
$web_page .= $cgi_obj -> h2("-- CONTENIDO CON OPCIONES DE LINEA DE COMANDOS --");
$web_page .= "</b></u>\n";
do_everything();

# Procesamos las opciones y trabajamos
# de la manera que el usuario especificó.
if ($opt_an and $opt_na)
{
	$web_page .= "<b><u>\n\t";
	$web_page .= $cgi_obj -> h2("-- CONTENIDO CON NOMBRE POR DEFECTO --");
	$web_page .= "</b></u>\n";

	$opt_na = 0;
	do_everything();
}

if ($opt_sw and $opt_si)
{
	$web_page .= "<b><u>\n\t";
	$web_page .= $cgi_obj -> h2("-- CONTENIDO CON SEXO POR DEFECTO --");
	$web_page .= "</b></u>\n";
	
	$opt_sw = 0;
	do_everything();
}

if ($opt_mn and $opt_mw)
{
	$web_page .= "<b><u>\n\t";
	$web_page .= $cgi_obj -> h2("-- CONTENIDO CON FECHA POR DEFECTO --");
	$web_page .= "</b></u>\n";
	
	$opt_mw = 0;
	do_everything();
}

end_web_page();


# Función que se encarga de realizar las tareas
# que el usuario especificó en la línea de comandos.
sub do_everything ()
{
	if ($opt_od)
	{
		put_ord_by_date();
	}

	if ($opt_os)
	{	
		put_ord_by_student();
	}

	if (@opt_sd)
	{
		foreach $in_date (@opt_sd)
		{
			put_sum_by_date($in_date);
		}
	}

	if (@opt_ss)
	{
		foreach $in_student (@opt_ss)
		{
			put_sum_by_student($in_student);
		}
	}

	if ($opt_t)
	{	
		$web_page .= $cgi_obj -> h2("<u><b>INFORME TOTALIZADO:</b></u>");
		
		my @person = keys %{ $people{ "PERS" } };

		foreach (@person)
		{
			$_ = change_name($_);
		}

		foreach $p (sort @person)
		{
			$p = corr_name($p);

			put_sum_by_student($p);
		}

		my @dates = keys %{ $people{ "DATE" } };

		foreach $d (sort @dates)
		{
			put_sum_by_date($d);
		}
	}
}

# Imprime los registros ordenados por fecha.
sub put_ord_by_date ()
{
	# A continuación se imprime la primer
	# fila de la tabla (el encabezado).

	$web_page .= "<p>\n";
	$web_page .= $cgi_obj -> h2("Ordenado por fecha: ");
	$web_page .= "<p>\n";
	
	$web_page .= "<table border=\"1\">\n";
	$web_page .= "<tr>\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Fecha");
	$web_page .= "</td>";
	$web_page .= "\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Materia");
	$web_page .= "</td>";
	$web_page .= "\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Alumno");
	$web_page .= "</td>";
	$web_page .= "\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Matricula");
	$web_page .= "</td>";
	$web_page .= "\n";

	
	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Nota");
	$web_page .= "</td>";
	$web_page .= "\n";


	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Profesor");
	$web_page .= "</td>";
	$web_page .= "\n";

	$web_page .= "</tr>\n";

	# Se imprime el cuerpo de la tabla.

	foreach $d (sort keys %{ $people{"DATE"} })
	{
		foreach $p (keys %{ $people{"DATE"}{$d} })
		{
			foreach $s (keys %{ $people{"DATE"}{$d}{$p} })
			{
				my $opt_date = set_date_as_req($d);
				my $opt_name = set_name_as_req($p);
				my $opt_sex = set_sex_as_req($people{$p}{"SEX"});
				my $subject = set_subj_as_req($s);
				my $comp_grade = get_complex_grade($people{"DATE"}{$d}{$p}{$s}[0]);
				
				$web_page .= "<tr>\n";

				$web_page .= "<td>";
				$web_page .= "$opt_date";
				$web_page .= "</td>\n";
				
				$web_page .= "<td>";
				$web_page .= "$subject";
				$web_page .= "</td>\n";
				
				$web_page .= "<td>";
				$web_page .= "$opt_name ($people{$p}{'AGE'}, $opt_sex)";
				$web_page .= "</td>\n";
				
				$web_page .= "<td>";
				$web_page .= "$people{$p}{'NUM'}";
				$web_page .= "</td>\n";
				
				$web_page .= "<td>";
				$web_page .= "$comp_grade";
				$web_page .= "</td>\n";
				
				$web_page .= "<td>";
				$web_page .= "$people{'DATE'}{$d}{$p}{$s}[1]";
				$web_page .= "</td>\n";

				$web_page .= "</tr>\n";
			}
		}
	}

	$web_page .= "</table\n>";
	$web_page .= "<p><p>\n";
}

# Idem put_ord_by_date() pero según estudiantes.
sub put_ord_by_student ()
{
	$web_page .= "<p>\n";
	$web_page .= $cgi_obj -> h2("Ordenado por alumno: ");
	$web_page .= "</p>\n";

	$web_page .= "<table border=\"1\">\n";

	$web_page .= "<tr>\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Alumno");
	$web_page .= "</td>";
	$web_page .= "\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Matricula");
	$web_page .= "</td>";
	$web_page .= "\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Materia");
	$web_page .= "</td>";
	$web_page .= "\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Nota");
	$web_page .= "</td>";
	$web_page .= "\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Fecha");
	$web_page .= "</td>";
	$web_page .= "\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Profesor");
	$web_page .= "</td>";
	$web_page .= "\n";
	
	$web_page .= "</tr>\n";

	my @keys_name = keys %{ $people{"PERS"} };
	
	foreach (@keys_name)
	{
		$_ = change_name($_);
	}
	
	foreach $p (sort @keys_name)
	{
		$p = corr_name($p);
	
		foreach $d (keys %{ $people{"PERS"}{$p} })
		{
			foreach $s (keys %{ $people{"PERS"}{$p}{$d} })
			{
				my $opt_date = set_date_as_req($d);
				my $opt_name = set_name_as_req($p);
				my $opt_sex = set_sex_as_req($people{$p}{"SEX"});
				my $subject = set_subj_as_req($s);
				my $comp_grade = get_complex_grade($people{"DATE"}{$d}{$p}{$s}[0]);
				
				$web_page .= "<tr>\n";

				$web_page .= "<td>";
				$web_page .= "$opt_name ($people{$p}{'AGE'}, $opt_sex)";
				$web_page .= "</td>\n";
				
				$web_page .= "<td>";
				$web_page .= "$people{$p}{'NUM'}";
				$web_page .= "</td>\n";
				
				$web_page .= "<td>";
				$web_page .= "$subject";
				$web_page .= "</td>\n";
				
				$web_page .= "<td>";
				$web_page .= "$comp_grade";
				$web_page .= "</td>\n";
				
				$web_page .= "<td>";
				$web_page .= "$opt_date";
				$web_page .= "</td>\n";
				
				$web_page .= "<td>";
				$web_page .= "$people{'PERS'}{$p}{$d}{$s}[1]";
				$web_page .= "</td>\n";

				$web_page .= "</tr>\n";
			}
		}
	}
	
	$web_page .= "</table\n>";
	$web_page .= "<p><p>\n";
}


# Imprime la información sumarizando por fecha.
# Trabaja de manera similar a put_ord_by_date().
sub put_sum_by_date ()
{
	my $date = $_[0];
	my $opt_date = set_date_as_req($date);
	my @subj_date = get_subj_by_date($date);
	
	$web_page .= "<p>\n";
	$web_page .= $cgi_obj -> h2("Sumarizado por fecha: $opt_date");
	$web_page .= "</p>\n";
	$web_page .= "<p>\n";
	$web_page .= $cgi_obj -> h3("Materias rendidas/aprobadas: $subj_date[0]/$subj_date[1]");
	$web_page .= "</p>\n";

	$web_page .= "<table border=\"1\">\n";

	$web_page .= "<tr>\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Alumno");
	$web_page .= "</td>";
	$web_page .= "\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Matricula");
	$web_page .= "</td>";
	$web_page .= "\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Materia");
	$web_page .= "</td>";
	$web_page .= "\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Nota");
	$web_page .= "</td>";
	$web_page .= "\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Profesor");
	$web_page .= "</td>";
	$web_page .= "\n";
	
	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Aprobada");
	$web_page .= "</td>";
	$web_page .= "\n";
	
	$web_page .= "</tr>\n";

	foreach $p (keys %{ $people{"DATE"}{$date} })
	{
		foreach $s (keys %{ $people{"DATE"}{$date}{$p} })
		{
			my $opt_name = set_name_as_req($p);
			my $opt_sex = set_sex_as_req($people{$p}{"SEX"});
			my $subject = set_subj_as_req($s);
			my $comp_grade = get_complex_grade($people{"DATE"}{$date}{$p}{$s}[0]);
			
			$web_page .= "<tr>\n";
			
			$web_page .= "<td>";
			$web_page .= "$opt_name ($people{$p}{'AGE'}, $opt_sex)";
			$web_page .= "</td>\n";
			
			$web_page .= "<td>";
			$web_page .= "$people{$p}{'NUM'}";
			$web_page .= "</td>\n";
			
			$web_page .= "<td>";
			$web_page .= "$subject";
			$web_page . "</td>\n";
		
			$web_page .= "<td>";
			$web_page .= "$comp_grade";
			$web_page .= "</td>\n";
			
			$web_page .= "<td>";
			$web_page .= "$people{'DATE'}{$date}{$p}{$s}[1]";
			$web_page .= "</td>\n";
			
			if ($comp_grade < 4)
			{
				$web_page .= "<td>";
				$web_page .= "NO";
				$web_page .= "</td>\n";
			}
			else
			{
				$web_page .= "<td>";
				$web_page .= "SI";
				$web_page .= "</td>\n";
			}
			
			$web_page .= "</tr>\n";
		}
	}
	
	$web_page .= "</table\n>";
	$web_page .= "<p><p>\n";
}


# Idem put_sum_by_date() sólo que en
# función de estudiantes.
sub put_sum_by_student ()
{
	my $person = $_[0];
	my $opt_name = set_name_as_req($person);
	my $num = $people{ $person }{ "NUM" };
	my $age = $people{ $person }{ "AGE" };
	my $opt_sex = set_sex_as_req($people{ $person }{ "SEX" });
	my @subj_name = get_subj_by_name($person);
	
	$web_page .= "<p>\n";
	$web_page .= 
	$cgi_obj -> h2("Sumarizado por alumno: $opt_name. Matricula: $num. Edad: $age. Sexo: $opt_sex");

	$web_page .= "</p>\n";
	$web_page .= "<p>\n";
	$web_page .= $cgi_obj -> h3("Materias rendidas/aprobadas: $subj_name[0]/$subj_name[1]");
	$web_page .= "</p>\n";

	$web_page .= "<table border=\"1\">\n";

	$web_page .= "<tr>\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Materia");
	$web_page .= "</td>";
	$web_page .= "\n";

	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Nota");
	$web_page .= "</td>";
	$web_page .= "\n";
	
	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Fecha");
	$web_page .= "</td>";
	$web_page .= "\n";
	
	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Profesor");
	$web_page .= "</td>";
	$web_page .= "\n";
	
	$web_page .= "<td>";
	$web_page .= $cgi_obj -> b("Aprobada");
	$web_page .= "</td>";
	$web_page .= "\n";

	$web_page .= "</tr>\n";


	foreach $d (keys %{ $people{"PERS"}{$person} })
	{
		foreach $s (keys %{ $people{"PERS"}{$person}{$d} })
		{
			my $opt_date = set_date_as_req($d);
			my $subject = set_subj_as_req($s);
			my $comp_grade = get_complex_grade($people{"PERS"}{$person}{$d}{$s}[0]);
			
			$web_page .= "<tr>\n";
			
			$web_page .= "<td>";
			$web_page .= "$subject";
			$web_page .= "</td>\n";
			
			$web_page .= "<td>";
			$web_page .= "$comp_grade";
			$web_page .= "</td>\n";
			
			$web_page .= "<td>";
			$web_page .= "$opt_date";
			$web_page . "</td>\n";
			
			$web_page .= "<td>";
			$web_page .= "$people{'PERS'}{$person}{$d}{$s}[1]";
			$web_page . "</td>\n";
			
			if ($comp_grade < 4)
			{
				$web_page .= "<td>";
				$web_page .= "NO";
				$web_page . "</td>\n";
			}
			else
			{
				$web_page .= "<td>";
				$web_page .= "SI";
				$web_page . "</td>\n";
			}
			
			$web_page .= "</tr>\n";
		}
	}
	
	$web_page .= "</table\n>";
	$web_page .= "<p><p>\n";
}


# Función encargada de, si se quiere mostrar el
# nombre bajo la opción Nombre y Apellido, 
# devolver el nombre de dicha forma.
sub change_name ()
{
	my $name = $_[0];

	if ($opt_na)
	{
		$name =~ s#(\w+) \. (\w+) \. (\w*)#$2.$3.$1#x;
	}

	return $name;
}

# Función encargada de, si se ha impreso el
# nombre bajo la opción Nombre y Apellido, 
# devolver el nombre en forma de clave válida
# para las estructuras hash.
sub corr_name ()
{
	my $name = $_[0];

	if ($opt_na)
	{
		$name =~ s#(\w+) \. (\w*) \. (\w+)#$3.$1.$2#x;
	}

	return $name;
}

# Función que, si se especificó que se quieren
# ver los meses como palabras, devuelve en 
# dicho formato. De otra manera, devuelve en
# el formato original.
sub set_date_as_req ()
{
	my $date = $_[0];

	if ($opt_mw)
	{
		$date =~ s#(\d+) \. (\d+) \. (\d+)#$3 de $MONTHS{$2} de $1#x;
	}
	else
	{
		$date =~ s#(\d+) \. (\d+) \. (\d+)#$3 / $2 / $1#x;
	}

	return $date;
}

# Devuelve el nombre en un formato cómodo para
# el usuario, además de acomodar según las opciones
# na o an (lo que corresponda).
sub set_name_as_req ()
{
	my $name = $_[0];

	if ($opt_na)
	{
		$name =~ s#(\w+) \. (\w+) \. (\w*)#$2 $3 $1#x;
	}
	else
	{
		$name =~ s#(\w+) \. (\w+) \. (\w*)#$1, $2 $3#x;
	}

	return $name;
}

# Función que devuelve el sexo en forma
# de palabra o en forma de inicial, según se
# haya especificado.
sub set_sex_as_req ()
{
	my $sex = $_[0];

	if ($opt_sw)
	{
		$sex = $SEX{ $sex };
	}

	return $sex;
}

# Función que devuelve el nombre de la materia
# en un formato cómodo para el usuario.
sub set_subj_as_req ()
{
	my $subj = $_[0];

	$subj =~ s#(\w+) \.#$1 #xg;

	return $subj;
}

# Función que retorna con un string que
# indica la nota en forma numérica y de texto.
# Por ej.: 5 Cinco. Utiliza la hash %GRADES.
sub get_complex_grade ()
{
	my $grade = $_[0];

	$grade .= " ";
	$grade .= $GRADES{ $grade };

	return $grade;
}

# Función que devuelve un array con la cantidad
# de materias rendidas y aprobadas para una determinada fecha.
sub get_subj_by_date ()
{
	my $date = $_[0];
	my $taken = 0;
	my $passed = 0;

	foreach $p (keys %{ $people{"DATE"}{$date} })
	{
		foreach $s (keys %{ $people{"DATE"}{$date}{$p} })
		{
			my $grade = $people{"DATE"}{$date}{$p}{$s}[0];

			if ($grade > 3)
			{
				$passed += 1;
			}

			$taken += 1;
		}
	}

	@subj_date = ($taken, $passed);

	return @subj_date;
}

# Idem get_subj_by_date() sólo que para un
# cierto estudiante.
sub get_subj_by_name ()
{
	my $person = $_[0];
	my $taken = 0;
	my $passed = 0;

	foreach $d (keys %{ $people{"PERS"}{$person} })
	{
		foreach $s (keys %{ $people{"PERS"}{$person}{$d} })
		{
			my $grade = $people{"PERS"}{$person}{$d}{$s}[0];

			if ($grade > 3)
			{
				$passed += 1;
			}

			$taken += 1;
		}
	}

	@subj_name = ($taken, $passed);

	return @subj_name;
}

# Almacena la información de los registros
# en una estructura de datos llamada %people.
# En esta función se guardan todos los datos, 
# excepto el sexo, la edad y el nro. de matrícula
# de la persona en cuestión.
sub save_in_people ()
{
	my $now_person = $_[0];
	my $now_subj = $_[1];
	my $now_grade = $_[2];
	my $now_date = $_[3];
	my $now_profe = $_[4];

	$people{"PERS"}{$now_person}{$now_date}{$now_subj} = [$now_grade, $now_profe];
	$people{"DATE"}{$now_date}{$now_person}{$now_subj} = [$now_grade, $now_profe];
}

# Función que devuelve la fecha del registro
# en un formato estándar, utilizado para usar
# la fecha como clave de la estructura %people.
sub get_date ()
{
	my $now_year = $_[0];
	my $now_month = std_date($_[1]);
	my $now_day = std_date($_[2]);

	if ($now_year < 50)
	{
		$now_year += 2000;
	}
	elsif ($now_year < 1950)
	{
		$now_year += 1900;
	}

	my $now_date = $now_year.".".$now_month.".".$now_day;

	return $now_date;
}


# Subrutina que se encarga de estandarizar
# el formato de las fechas (en caso de tener
# como dia o mes un valor de la forma n, se
# devuelve 0n. Si se tiene como formato 0n, 
# se devuelve el mismo valor.
sub std_date ()
{
	my $std_dat = $_[0];

	if ($std_dat < 10)
	{
		unless ($std_dat =~ m/^0/)
		{
			$std_dat =~ s#(\d+)#0$1#;
		}
	}

	return $std_dat;
}

# Función encargada de inicializar las
# variables $cgi_obj y $web_page, encargadas
# de almacenar la información de la página web.
# También abre el file descriptor WEB_PAGE que
# apunta al archivo que contendrá la página (el
# archivo HTML indicado bajo la opción -o).
sub start_web_page ()
{
	$cgi_obj = new CGI;
	$now_time = localtime();

	if ($opt_o)
	{
		open(WEB_PAGE, ">$opt_o");
	}
	else
	{
		open(WEB_PAGE, ">alumnos_out.html");	# Nombre por defecto.
	}

	$web_page = $cgi_obj -> start_html("Listado de alumnos");

	$web_page .= $cgi_obj -> h1("Informe de alumnos fecha: $now_time");

	my $args = "";
	foreach $arg (@args)
	{
		$args .= "$arg ";
	}
	$web_page .= $cgi_obj -> h2("Opciones pasadas al programa: $args");

	$web_page .= "<p><p> \n";
}

# Imprime toda la información almacenada en
# $web_page, dentro del archivo HTML, y cierra
# dicho archivo.
sub end_web_page ()
{
	$web_page .= $cgi_obj -> end_html();

	print (WEB_PAGE "$web_page");

	close(WEB_PAGE);
}
