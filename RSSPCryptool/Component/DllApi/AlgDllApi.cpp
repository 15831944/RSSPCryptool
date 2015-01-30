//unicode��һ���ַ�ռ2�ֽڣ�����2��char�ĳ���

#include "stdafx.h"
#include "AlgDllApi.h"

/***********************DllMng��ʵ��******************************/
DllMng::DllMng(){
	getDllDir();
	LoadDlls();
	getAllCipher();
}
DllMng::~DllMng(){
	FreeDlls();
}

void DllMng::getDllDir(){
	char buff[100];
	int len = 0;
	cfgFile.open("Config.txt",ios::in);
	if(cfgFile.is_open()){
		while(!cfgFile.eof()){
			cfgFile.read(buff+len,1);
			if(buff[len] == ';') break;
			len++;
		}
	}else dllDir = "ERROR";
	dllDir =  CString(buff,len);
}

void DllMng::LoadDlls(){
	CString dir(dllDir);
	dir.Append(_T("*.dll"));

	bool succ = finder.FindFile(dir.GetBuffer());
	while(succ){
		succ = finder.FindNextFile();

		dir = dllDir;
		dir.Append(finder.GetFileName());

		handles.Add(DLL_OPEN(dir));
	}
	for(int i = 0;i < handles.GetSize();i++){
		cout<<handles.GetAt(i)<<endl;
	}
}

void DllMng::FreeDlls(){
	for(int i = 0;i < handles.GetSize();i++){
		DLL_CLOSE(handles.GetAt(i));
	}
	handles.RemoveAll();
}

//����Dll��Ψһ�ı���
void * DllMng::getAlgFun(CString name){
	void *p = NULL;
	for(int i = 0;i < handles.GetSize();i++){
		p = DLL_GET(handles.GetAt(i),name);
		if(p != NULL) break;
	}
	return p;
}

void DllMng::getAllCipher(){
	Cipher * head = NULL;

	for(int i = 0;i < handles.GetSize();i++){
		head = (Cipher *)DLL_GET(handles.GetAt(i),"CIPHERS");
		
		int amount = *(int *)DLL_GET(handles.GetAt(i),"B_AMOUNT");
		amount += *(int *)DLL_GET(handles.GetAt(i),"S_AMOUNT");
		amount += *(int *)DLL_GET(handles.GetAt(i),"H_AMOUNT");
		amount += *(int *)DLL_GET(handles.GetAt(i),"M_AMOUNT");
		amount += *(int *)DLL_GET(handles.GetAt(i),"R_AMOUNT");

		for(int j = 0;j < amount;j++) ciphers.Add(head + j);
	}

	
	cout<<ciphers.GetSize()<<endl;
	for(int i = 0;i < 53;i++){
		Cipher * c = ciphers.GetAt(i);
		
		puts(c->DllName);
		cout<<','<<c->AlgType<<',';
		puts(c->AlgName);
		cout<<c->key_len<<','<<c->output_len<<','
			<<c->iv_len<<','<<c->block_size<<','
			<<c->seed_len<<endl;
	}
}

CArray<HCIPHER> * DllMng::getCiphers(){
	if(ciphers.GetSize() == 0) getAllCipher();
	return &ciphers;
}

/***********************AlgMng��ʵ��******************************/
AlgMng::AlgMng(DllMng * dllMng){
	this->dllMng = dllMng;
	info = dllMng->getCiphers();
	alg = new Cipher;
}

AlgMng::~AlgMng(){

}

/*�ú��������������BLOCK_SIZE��������,�����س���*/
int AlgMng::padding(byte ** msg,int o_len){
	int n_len = (o_len/alg->block_size + 1)*alg->block_size;
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

CString AlgMng::GetCurrentAlg(int type){
	return "nothing";
}

int AlgMng::GetCurrentMode(){
	return 0;
}

//�趨����Ҫʹ�õ��㷨
void AlgMng::setAlg(int type,CString name){
	for(int i = 0;i < info->GetSize();i++){
		Cipher * pc = info->GetAt(i);
		if(pc->AlgType == type && name.CompareNoCase(pc->AlgName) == 0){
			memcpy(alg,pc,sizeof(Cipher));
			break;
		}
	}
}

//�������ݣ���ȡ�����
/*��directΪtrueʱ,������ܣ�inputΪ���ģ��������ġ�
**��directΪfalseʱ��������ܣ�inputΪ���ġ��������ġ�
*/
//���ܡ�����ʧ��ʱ��������NULL
byte * AlgMng::RunCipher(bool direct,byte* input,int len,byte* key,int mode,byte *iv){
	pBlockCipher Block = (pBlockCipher)(dllMng->getAlgFun("Use_" + CString(alg->AlgName)));
	byte * output = NULL;
	bool succ;

	output = new byte[len];
	int n_len = padding(&input,len);
	if(direct) succ = (*Block)(direct,key,alg->key_len,input,n_len,output,n_len,mode,iv,alg->block_size);
	else succ = (*Block)(direct,key,alg->key_len,output,n_len,input,n_len,mode,iv,alg->block_size);
	unpadding(&output,len);
	return succ ? output : NULL;
}

//int _tmain(int argc, _TCHAR* argv[])
//{
//	AlgMng mng(&dllMng);
//	mng.setAlg(BLOCK,"AES");
//
//	system("pause");
//	return 0;
//
//}