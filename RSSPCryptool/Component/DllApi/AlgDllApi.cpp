#include "AlgDllApi.h"

AlgMng::AlgMng(){
	alg = new Cipher;
	path_load = "AlgCfg.txt";
}

AlgMng::~AlgMng(){

}

/*�ú��������������BLOCK_SIZE��������,�����س���*/
int AlgMng::padding(byte ** msg,int o_len){
	int n_len = (o_len/alg->input_len + 1)*alg->input_len;
	byte * n_msg = new byte[n_len];
	memcpy(n_msg,*msg,o_len);
	//����Ҫ�ͷ�ԭ����ָ��
	*msg = n_msg;
	return n_len;
}

void AlgMng::unpadding(byte ** msg,int o_len){
	byte * n_msg = new byte[o_len];
	memcpy(n_msg,*msg,o_len);
	//����Ҫ�ͷ�ԭ����ָ��
	*msg = n_msg;
}

string AlgMng::GetCurrentAlg(int type){
	AlgLoadFile.open(path_load.data(),ios::in);
	if(!AlgLoadFile.is_open()) return "";

	string *AlgName;
	char line[50];
	while(!AlgLoadFile.eof()){
		AlgLoadFile.getline(line,50);
		if(type == atoi(line)){
			AlgName = new string(line,2,50);
			AlgName->assign(AlgName->substr(0,AlgName->find_first_of(' ',0)));
		}
	}
	AlgLoadFile.close();
	return *AlgName;
}

int AlgMng::GetCurrentMode(){
	AlgLoadFile.open(path_load.data(),ios::in);
	if(!AlgLoadFile.is_open()) return -1;

	char line[50];
	AlgLoadFile.getline(line,50);
	AlgLoadFile.close();
	return atoi(line + (strlen(line)-2));
}

//void AlgMng::GetDllCipher(int AlgType,string AlgName){
//	string FunName = "Use_";
//	string path(path_dll);
//	//����DLL
//	path.append(GetDllName(AlgName).data());
//	dll = DLL_OPEN(path.data());
//	FunName.append(AlgName);
//	//��ȡ�ṹ������
//	Cipher * cipher_list;
//	int *amount = NULL;
//	switch(AlgType){
//	case BLOCK:cipher_list = (Cipher *)DLL_GET(dll,"BLOCK_CIPHERS");amount = (int *)DLL_GET(dll,"B_AMOUNT");
//		break;
//	case STREAM:cipher_list = (Cipher *)DLL_GET(dll,"STREAM_CIPHERS");amount = (int *)DLL_GET(dll,"S_AMOUNT");
//		break;
//	case HASH:cipher_list = (Cipher *)DLL_GET(dll,"HASH_CIPHERS");amount = (int *)DLL_GET(dll,"H_AMOUNT");
//		break;
//	case MAC:cipher_list = (Cipher *)DLL_GET(dll,"MAC_CIPHERS");amount = (int *)DLL_GET(dll,"M_AMOUNT");
//		break;
//	case RNG:cipher_list = (Cipher *)DLL_GET(dll,"RNG_CIPHERS");amount = (int *)DLL_GET(dll,"R_AMOUNT");
//		break;
//	}
//	for(int i = 0;i < *amount;i++){
//		if(strcmp(cipher_list[i].AlgName,AlgName.data()) == 0){
//			memcpy(c,&cipher_list[i],sizeof(Cipher));
//			alg->pFun = DLL_GET(dll,FunName.data());
//			break;
//		}
//	}
//	//DLL_CLOSE(dll);
//	//��ϸ�����ͷ�ʱ�䣻
//}

//bool AlgMng::RunCipher(){
//	pBlockCipher Block;
//	pStreamCipher Stream;
//	pHashFuction Hash;
//	pMacConstructor Mac;
//	pRng Rng;
//
//	switch(alg->AlgType){
//	case BLOCK:
//		Block = (pBlockCipher)(alg->pFun);
//		return (*Block)(alg->direct,alg->key,alg->key_len,alg->input,alg->input_len,
//			alg->output,alg->output_len,alg->mode,alg->iv,alg->block_size);
//	case STREAM:
//		Stream = (pStreamCipher)(alg->pFun);
//		return (*Stream)(alg->direct,alg->key,alg->key_len,alg->input,alg->input_len,
//			alg->output,alg->output_len,alg->iv,alg->iv_len);
//	case HASH:
//		Hash = (pHashFuction)(alg->pFun);
//		return (*Hash)(alg->input,alg->output,alg->output_len);
//	case MAC:
//		Mac = (pMacConstructor)(alg->pFun);
//		return (*Mac)(alg->key,alg->key_len,alg->input,alg->input_len,alg->output,alg->output_len,alg->iv);
//	case RNG:
//		Rng = (pRng)(alg->pFun);
//		alg->output = (*Rng)(alg->seed,alg->output_len);
//
//		if(alg->output != NULL) return true;
//		else return false;
//	default: return false;
//	}
//}

//�������ݣ���ȡ�����
/*��directΪtrueʱ,������ܣ�inputΪ���ģ��������ġ�
**��directΪfalseʱ��������ܣ�inputΪ���ġ��������ġ�
*/
//���ܡ�����ʧ��ʱ��������NULL
byte * AlgMng::RunCipher(bool direct,byte* input,int len,byte* key,int mode,byte *iv){
	pBlockCipher Block = (pBlockCipher)(alg->pFun);
	byte * output = NULL;
	bool succ;

	output = new byte[len];
	int n_len = padding(&input,len);
	if(direct) succ = (*Block)(direct,key,alg->key_len,input,n_len,output,n_len,mode,iv,alg->block_size);
	else succ = (*Block)(direct,key,alg->key_len,output,n_len,input,n_len,mode,iv,alg->block_size);
	unpadding(&output,len);
	return succ ? output : NULL;
}

//byte * AlgMng::RunCipher(bool direct,byte* input,int len,byte* key,byte* iv){
//	alg->key = key;
//	alg->iv = iv;
//	alg->direct = direct;
//	if(direct){
//		alg->input = input;
//		alg->input_len = len;
//
//		alg->output_len = alg->input_len;
//		alg->output = new byte[alg->output_len];
//
//		RunCipher();
//		return alg->output;
//	}else{
//		alg->output = input;
//		alg->output_len = len;
//
//		alg->input_len = alg->output_len;
//		alg->input = new byte[alg->input_len];
//
//		RunCipher();
//		return alg->input;
//	}
//}
//
//byte * AlgMng::RunCipher(string msg){
//	alg->input = (byte *)msg.data();
//	alg->input_len = msg.length();
//	alg->output = new byte[alg->output_len];
//	RunCipher();
//	return alg->output;
//}
//
//byte * AlgMng::RunCipher(string input,byte* key,byte * iv){
//
//	alg->input = (byte *)input.data();
//	alg->input_len = input.length();
//	alg->key = key;
//	alg->iv = iv;
//	alg->output = new byte[alg->output_len];
//	/*Run֮��û������mac������iv*/
//	RunCipher();
//	return alg->output;
//}
//
//byte * AlgMng::RunCipher(int seed,int size){
//	alg->seed = seed;
//	alg->output_len = size;
//	alg->output = new byte[alg->output_len];
//	RunCipher();
//	return alg->output;
//}