class BTHashFunction {
	// 12 semicolon challenge :)
	
	static int infixFunction(int fnNumber, int x, int y)
	{
		if(fnNumber == 0) return x+2*y;
		if(fnNumber == 1) return 2*x+y;
		if(fnNumber == 2) return x+y;
		else return x*y; // assuming fnNumber is 3
	}

	static int twosComplement2Bit(int num)
	{ 
		// return 2's complement of 2bit number
		return num < 2 ? num : -(4 - (num & 0x3)); 
		// (num&0x3) -> just in case num is > 3
	}

	static int getBitValue(long bitNumber, int bitIndex)
	{
		return ((bitNumber & (1<<bitIndex)) != 0) ? 1 : 0;
	}

	static int get2BitNumber(long bitNumber, int bitIndex1, int bitIndex2)
	{
		return (getBitValue(bitNumber, bitIndex1) | 
				(getBitValue(bitNumber, bitIndex2) << 1));
	}

	static int btHashFunction(int nodeNumber, int curLevel, long bitNumber) 
	{
		if(curLevel >= 4) // leaf level - signed 2bit number
			return twosComplement2Bit(get2BitNumber(bitNumber, 
													2*nodeNumber, 
													2*nodeNumber+1));
		//else part
		return // internal nodes - perform operation
			infixFunction(get2BitNumber(bitNumber, 
										2*nodeNumber, 2*nodeNumber+1),
						  btHashFunction(2*nodeNumber+1, curLevel+1, bitNumber),
						  btHashFunction(2*nodeNumber+2, curLevel+1, bitNumber));
	}

	public static void main(String args[])
	{
		long curTime = System.currentTimeMillis();
		long curTime32GBitTime = (curTime & 0xFFFF) | ((curTime & 0xFFFF)<<16) |
			((curTime & 0xFFFF) << 32) | ((curTime & 0xFFFF) << 48);

		System.out.println("Current Time: " + curTime + 
						   "\nHash Value: " + 
						   btHashFunction(0, 0, curTime32GBitTime));
	}
}
