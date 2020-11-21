<h2>
"Propositional-Inference-using-dpll-algorithms" 
 </h2>
 
 <h3> input is taken from input.txt in form of clauses </h3>
 
	ex.
	( e<->f + !g ) 
	( a->g +h ) 
	(!a + b + c)
	(a + c + d)
<h2>
A SAT Solver based on the Davis-Putnam-Logemann-Loveland (DPLL) algorithm.
</h2>

<h2>
Prerequisites
	</h2>
	<h3>
g++ (or any other C++ compiler) with C++14 support </h3>
		
<h4>
	GNU make
		</h4>
	<h3>
for clone  </h3>

<ul>
	<li>git clone https://github.com/dnyaneshm36/Propositional-Inference-using-dpll-algorithms.git </li>
<li>cd Propositional-Inference-using-dpll-algorithms </li>
	</ul>
	
	
<h3>
Compile and run </h3>
<ul>
	<li> g++  -g  dpll.cpp -o dpll </li>
<li > cd  ./dpll </li>
	</ul>

 <h3> input  </h3>
 
	( e<->f + !g  )
	( a->g +h )
	(!a + b + c)
	(a + c + d)
	(a + c + !d)
	(a + !c +d)
	(a + !c + !d)
	(!b + !c +d)
	(!a + b + !c)
	(!a + !b + c)

	
 <h3> output  </h3>
	

	statiable :
	b 1
	g 0
	h 1
	c 1
	a 1
	d 1
	 ----statifable----

<h4>
 here b  = postive <br>
	 g   = negative <br>
	so on ..
	</h4>

