library IEEE;
use IEEE.std_logic_1164.all;
library unisim;
use unisim.vcomponents.all;

entity v2to4dec is
    port (  EN : in   STD_LOGIC;
            I1 : in   STD_LOGIC;
            I0 : in   STD_LOGIC;
            Y0 : out  STD_LOGIC;
            Y1 : out  STD_LOGIC;
            Y2 : out  STD_LOGIC;
            Y3 : out  STD_LOGIC );
end v2to4dec;

architecture v2to4dec_arch of v2to4dec is
signal I0_L, I1_L: STD_LOGIC;
component INV port(I: in STD_LOGIC; O: out STD_LOGIC); end component;
component AND3 port(I0, I1, I2: in STD_LOGIC; O: out STD_LOGIC); end component;
begin
    U1: INV port map (I1, I1_L);
    U2: INV port map (I0, I0_L);
    U3: AND3 port map (EN, I1_L, I0_L, Y0);
    U4: AND3 port map (EN, I1_L, I0, Y1);
    U5: AND3 port map (EN, I1, I0_L, Y2);
    U6: AND3 port map (EN, I1, I0, Y3);
end v2to4dec_arch;