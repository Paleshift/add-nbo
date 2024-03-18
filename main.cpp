#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>

int main(int num_parameter, char *name_parameter[]){
	//"num_parameter" means the numeber of parameter divisible by "space"
	//"*name_parameter[]" means the address of each parameter divisible by "space"
	//For example, name_parameter[0] = ./add-nbo

	FILE *file1;
	file1 = fopen(name_parameter[1], "rb");
	//Open file1
	
	if(file1==NULL){
		printf("Error!");
		return 0;
	}
	//Check whether file1 is successfully opened
	
	int size_file1;
	fseek(file1, 0, SEEK_END);
	//Move to end of file1 
	size_file1 = ftell(file1);
	//Save the size of flie1
	//Cf) (The location of end of file1)=(Size of file1)
	if(size_file1==4){
		fseek(file1, 0, SEEK_SET);
	}
	else{
		printf("Error!");
		return 0;
	}
	//Check whether the size of flie1 is exactly 4Bytes

	FILE *file2;
	file2 = fopen(name_parameter[2], "rb");
	
	if(file2==NULL){
		printf("Error!");
		return 0;
	}
	
	int size_file2;
	fseek(file2, 0, SEEK_END);
	size_file2 = ftell(file2);
	if(size_file2==4){
		fseek(file2, 0, SEEK_SET);
	}
	else{
		printf("Error!");
		return 0;
	}
	//Same as before
	
	uint8_t nbo_buffer1[4];
	fread(nbo_buffer1, sizeof(uint8_t), 4, file1);
	//Save 32Bit number from file1 to nbo_buffer1[4] by nbo
	uint32_t *hbo1 = reinterpret_cast<uint32_t*>(nbo_buffer1);
	uint32_t after1= ntohl(*hbo1);
	//Save the 32Bit number to after1 consider hbo
	
	uint8_t nbo_buffer2[4];
	fread(nbo_buffer2, sizeof(uint8_t), 4, file2);
	uint32_t *hbo2 = reinterpret_cast<uint32_t*>(nbo_buffer2);
	uint32_t after2= ntohl(*hbo2);
	//Same as before
	
	fclose(file1);
	fclose(file2);
	//Close file1 and file2
	
	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)", after1, after1, after2, after2, after1+after2, after1+after2);

	return 0;

}
