// 원하는 소자 -> 회로도에서 핀 찾음 -> 해당 핀에 대한 정보를 찾음 (어떤 레지스터의 어떤 비트?)

#define GPDR1 (*(volatile int *)0x40e00010) // 0x40e00010 부터 시작하는 4바이트의 주소의 값을 참조.
// volatile : Optimization 하지 않고 있는 그대로의 값을 사용 (Interrupt에 의한 값 변화시 그 값을 읽기 위함.)
#define GPCR1 (*(volatile int *)0x40e00028) 
#define GPSR1 (*(volatile int *)0x40e0001c)
#define GPDR2 (*(volatile int *)0x40e00014)
#define GPCR2 (*(volatile int *)0x40e0002c)
#define GPSR2 (*(volatile int *)0x40e00020)

int main()
{
	int i = 0;

    // GPIO Direction Register, 데이터 I/O 방향 지정
	GPDR1 |= 0x00100000; // GPDR1 의 해당 비트(GPIO52)에 True를 마스킹 (OUTPUT 으로 사용)
	GPDR2 |= 0x00040000; // GPDR2 의 해당 비트(GPIO82)에 True를 마스킹 (OUTPUT 으로 사용) 

	while(1)
	{
        // GPIO Clear Register
		GPCR1 |= 0x00100000; // 해당 비트 (GPIO52) False 로 셋, False 일 때 LED 점등 (OR 연산으로 원하는 자리만 마스킹)
		for(i=0;i<1000000;i++); // 1000000[word] 만큼 지연
        // GPIO Set Register
		GPSR1 |= 0x00100000; // 해당 비트 (GPIO52) True 로 셋, True 일 때 LED 점등


		GPCR2 |= 0x00040000; // 해당 비트 (GPIO82) False 로 셋.
		for(i=0;i<1000000;i++); // 1000000[word] 만큼 지연
		GPSR2 |= 0x00040000; // 해당 비트 (GPIO82) True 로 셋.
	}
    // GPDR0~3, GPCR0~3, GPSR0~3 으로 총 4개 존재, 4바이트씩 끊어서 몇번 GPIO가 있는지 추측 가능. 

    // GPDR0~3 : 1 -> OUTPUT, 0 -> INPUT (Direction)
    // GPCR0~3 : 1 -> False (Clear), 0 -> 영향없음 (※ Not True)
    // GPSR0~3 : 1 -> True (Set), 0 -> 영향없음 (※ Not False)
	
}