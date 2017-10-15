library ieee;
use ieee.std_logic_1164.all;

entity CPUstream is
   port(SWC,SWB,SWA,IR7,IR6,IR5,IR4,W1,W2,W3,C,Z,T3,CLR:in std_logic;--控制台命令SWC~SWA 运算器命令IR7~IR4 时序W1~W3 清零信号CLR
        LDZ,LDC,CIN,S0,S1,S2,S3,M:out std_logic;
        DRW,PCINC,LPC,LAR,PCADD,ARINC,SELCTL,MEMW,STOP,LIR,SBUS,MBUS,ABUS,SHORT,LONG,SEL0,SEL1,SEL2,SEL3:out std_logic);
end CPUstream;

architecture func of CPUstream is--硬连线控制器功能定义

   signal ST0:std_logic;--控制台控制信号
   signal SST0:std_logic;--标记位
   signal IR:std_logic_vector(7 downto 4);
   signal SW:std_logic_vector(2 downto 0);
begin
   process(W1,W2,CLR,SST0)--敏感信号列表
   begin
    LDZ<='0';
	LDC<='0';
	CIN<='0';
	S0<='0';
	S1<='0';
	S2<='0';
	S3<='0';
	M<='0';
	DRW<='0';
	PCINC<='0';
	LPC<='0';
	LAR<='0';
	PCADD<='0';
	ARINC<='0';
	SELCTL<='0';
	MEMW<='0';
	STOP<='0';
	LIR<='0';
	SBUS<='0';
	MBUS<='0';
	ABUS<='0';
	SHORT<='0';
	LONG<='0';
	SEL0<='0';
	SEL1<='0';
	SEL2<='0';
	SEL3<='0'; 
    SW<=SWC&SWB&SWA;
    if (CLR = '0') then--当CLR信号有效时，SST0和ST0都置0
		ST0 <= '0';
		SST0 <= '0';
	elsif (T3'event and T3 = '0') then--ST0变化，控制台变化	
		ST0 <= SST0;
	end if;
    case SW is--各信号有效条件，高低均有定义的信号只确定其高有效的表达式
	when "100"=>
		SBUS<=W1 or W2;
		SELCTL<=W1 or W2;
		STOP<=W1 or W2;
		DRW<=W1 or W2;
	if ST0='0' then
		SEL1<=W1;
		SEL0<=W1;
		SEL2<=W2;
		SST0<=W2;
	else
		SEL3<=W1 or W2;
		SEL0<=W1;
		SEL2<=W2;
		SEL1<=W2;
		SST0<=not W2;
		end if;
	when "011"=>
		SEL0<=W1 or W2;
		SELCTL<=W1 or W2;
		STOP<=W1 or W2;
		SEl3<=W2;
		SEL1<=W2;
	when "010"=>
		STOP<=W1;
		SHORT<=W1;
		SELCTL<=W1;
	if ST0='0' then
		SBUS<=W1;
		LAR<=W1;
		SST0<=W1;
	else
		MBUS<=W1;
		ARINC<=W1;
	end if;
	when "001"=>
		SBUS<=W1;
		STOP<=W1;
		SHORT<=W1;
		SELCTL<=W1;
	if ST0='0' then
		LAR<=W1;
		SST0<=W1;
	else
		MEMW<=W1;
		ARINC<=W1;
	end if;
	when "000"=>
		IR<=IR7&IR6&IR5&IR4;
		case IR is
			when "0000"=>
				LIR<=W1;
				PCINC<=W1;
				SHORT<=W1;
			when "0001"=>     --   +
				S3<=W1;
				S0<=W1;
				CIN<=W1;
				ABUS<=W1;
				DRW<=W1;
				LDZ<=W1;
				LDC<=W1;
				LIR<=W1;
				PCINC<=W1;
				SHORT<=W1;
			when "0010"=>--  -
				S2<=W1;
				S1<=W1;
				ABUS<=W1;
				DRW<=W1;
				LDZ<=W1;
				LDC<=W1;
				LIR<=W1;
				PCINC<=W1;
				SHORT<=W1;
			when "0011"=> --AND
				S3<=W1;
				S1<=W1;
				S0<=W1;
				M<=W1;
				ABUS<=W1;
				DRW<=W1;
				LDZ<=W1;
				LIR<=W1;
				PCINC<=W1;
				SHORT<=W1;
			when "0100"=>--INC
				ABUS<=W1;
				DRW<=W1;
				LDZ<=W1;
				LDC<=W1;
				LIR<=W1;
				PCINC<=W1;
				SHORT<=W1;
			when "0101"=>--LD
				S3<=W1;
				S1<=W1;
				M<=W1;
				ABUS<=W1;
				LAR<=W1;
				DRW<=W2;
				MBUS<=W2;
				LIR<=W2;
				PCINC<=W2;
			when "0110"=>--ST
				S3<=W1 or  W2;
				S2<=W1;
				S1<=W1 or W2;
				S0<=W1;
				M<=W1 or W2;
				ABUS<=W1 or W2;
				LAR<=W1;
				MEMW<=W2;
				LIR<=W2;
				PCINC<=W2;
			when "0111"=>--JC
				PCADD<=W1 and C;
				LIR<=W2;
				PCINC<=W2;
			when "1000"=>--JZ
				PCADD<=W1 and Z;
				LIR<=W2;
				PCINC<=W2;
			when "1001"=>--JMP
				M<=W1;
				S3<=W1;
				S2<=W1;
				S1<=W1;
				S0<=W1;
				ABUS<=W1;
				LPC<=W1;
				LIR<=W2;
				PCINC<=W2;
			when "1110"=>
				STOP<=W1;
			when others=>null;
		end case;
	when others=>null;
	end case;
	end process;
end func;
