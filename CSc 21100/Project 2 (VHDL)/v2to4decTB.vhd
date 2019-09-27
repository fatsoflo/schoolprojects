library IEEE;
use IEEE.std_logic_1164.all;
library unisim;
use unisim.vcomponents.all;

entity v2to4decTB is
end v2to4decTB;

architecture v2to4decTB_arch of v2to4decTB is
	-- Component Declaration  
component v2to4dec port (EN, I1, I0: in STD_LOGIC; Y0, Y1, Y2, Y3: out STD_LOGIC); end component;
signal ENT, I1T, I0T : STD_LOGIC;
signal Y0T, Y1T, Y2T, Y3T : STD_LOGIC; 

begin

	-- Component Instantiation
	U1: v2to4dec port map (ENT, I1T, I0T, Y0T, Y1T, Y2T, Y3T);

	-- Test Bench Statements
	process
	begin
	-- Insert Stimulus 
	report "Beginning test bench for v2to4dec" severity NOTE;
	
	ENT <= '0'; I1T <= '0'; I0T <= '0'; wait for 10 ns;
	assert (Y0T = '0');    
	I1T <= '0'; I0T <= '1'; wait for 10 ns;
	assert (Y1T = '0');
	I1T <= '1'; I0T <= '0'; wait for 10 ns;
	assert (Y2T = '0');
	I1T <= '1'; I0T <= '1'; wait for 10 ns;
	assert (Y3T = '0');
	
	ENT <= '1'; I1T <= '0'; I0T <= '0'; wait for 10 ns;
	assert (Y0T = '1');
	I1T <= '0'; I0T <= '1'; wait for 10 ns;
	assert (Y1T = '1');
	I1T <= '1'; I0T <= '0'; wait for 10 ns;
	assert (Y2T = '1');
	I1T <= '1'; I0T <= '1'; wait for 10 ns;
	assert (Y3T = '1');
	
	report "Ending test bench for v2to4dec" severity NOTE;
	wait;
	end process;
	 
end v2to4decTB_arch;