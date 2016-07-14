// AnnBp.cpp: implementation of the CAnnBp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "AnnBp.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAnnBp::CAnnBp()
{
	m_Eta=0.3;
	m_Momentum=0.3;

}

CAnnBp::~CAnnBp()
{

}


double CAnnBp::drnd()
{
	return ((double) rand() / (double) BIGRND);
}


/*** 返回-1.0到1.0之间的双精度随机数 ***/
double CAnnBp::dpn1()
{
	return (double) (rand())/(32767/2)-1;
}

/*** 作用函数，目前是S型函数 ***/
double CAnnBp::squash(double x)
{
	return (1.0 / (1.0 + exp(-x)));
}


/*** 申请1维双精度实数数组 ***/
double* CAnnBp::alloc_1d_dbl(int n)
{
	double *new1;

	new1 = (double *) malloc ((unsigned) (n * sizeof (double)));
	if (new1 == NULL) {
		AfxMessageBox("ALLOC_1D_DBL: Couldn't allocate array of doubles\n");
		return (NULL);
	}
	return new1;
}

/*** 申请2维双精度实数数组 ***/
double** CAnnBp::alloc_2d_dbl(int m, int n)
{
	int i;
	double **new1;

	new1 = (double **) malloc ((unsigned) (m * sizeof (double *)));
	if (new1 == NULL) {
		AfxMessageBox("ALLOC_2D_DBL: Couldn't allocate array of dbl ptrs\n");
		return (NULL);
	}

	for (i = 0; i < m; i++) {
		new1[i] = alloc_1d_dbl(n);
	}

	return new1;
}


/*** 随机初始化权值 ***/
void CAnnBp::bpnn_randomize_weights(double **w, int m, int n)
{
	int i, j;
	for (i = 0; i <= m; i++) {
		for (j = 0; j <= n; j++) {
			w[i][j] = dpn1();
		}
	}

}

/*** 0初始化权值 ***/
void CAnnBp::bpnn_zero_weights(double **w, int m, int n)
{
	int i, j;

	for (i = 0; i <= m; i++) {
		for (j = 0; j <= n; j++) {
			w[i][j] = 0.0;
		}
	}

}

/*** 设置随机数种子 ***/
void CAnnBp::bpnn_initialize(int seed)
{
	CString msg,s;
	msg="Random number generator seed:";
	s.Format("%d",seed);
	AfxMessageBox(msg+s);
	srand(seed);
}

/*** 创建BP网络 ***/
BPNN* CAnnBp::bpnn_internal_create(int n_in, int n_hidden, int n_out)
{
	BPNN *newnet;

	newnet = (BPNN *) malloc (sizeof (BPNN));
	if (newnet == NULL) {
		printf("BPNN_CREATE: Couldn't allocate neural network\n");
		return (NULL);
	}

	newnet->input_n = n_in;
	newnet->hidden_n = n_hidden;
	newnet->output_n = n_out;
	newnet->input_units = alloc_1d_dbl(n_in + 1);
	newnet->hidden_units = alloc_1d_dbl(n_hidden + 1);
	newnet->output_units = alloc_1d_dbl(n_out + 1);

	newnet->hidden_delta = alloc_1d_dbl(n_hidden + 1);
	newnet->output_delta = alloc_1d_dbl(n_out + 1);
	newnet->target = alloc_1d_dbl(n_out + 1);

	newnet->input_weights = alloc_2d_dbl(n_in + 1, n_hidden + 1);
	newnet->hidden_weights = alloc_2d_dbl(n_hidden + 1, n_out + 1);

	newnet->input_prev_weights = alloc_2d_dbl(n_in + 1, n_hidden + 1);
	newnet->hidden_prev_weights = alloc_2d_dbl(n_hidden + 1, n_out + 1);

	return (newnet);

}

/* 释放BP网络所占地内存空间 */
void CAnnBp::bpnn_free()//BPNN *m_Net
{
	int n1, n2, i;

	n1 = m_Net->input_n;
	n2 = m_Net->hidden_n;

	free((void*) m_Net->input_units);
	free((void*) m_Net->hidden_units);
	free((void*) m_Net->output_units);

	free((void*) m_Net->hidden_delta);
	free((void*) m_Net->output_delta);
	free((void*) m_Net->target);

	for (i = 0; i <= n1; i++) {
		free((void*) m_Net->input_weights[i]);
		free((void*) m_Net->input_prev_weights[i]);
	}
	free((void*) m_Net->input_weights);
	free((void*) m_Net->input_prev_weights);

	for (i = 0; i <= n2; i++) {
		free((void*) m_Net->hidden_weights[i]);
		free((void*) m_Net->hidden_prev_weights[i]);
	}
	free((void*) m_Net->hidden_weights);
	free((void*) m_Net->hidden_prev_weights);

	free((void*) m_Net);
}


/*** 创建一个BP网络，并初始化权值***/
BPNN* CAnnBp::bpnn_create(int n_in, int n_hidden, int n_out)
{
	BPNN *newnet;

	newnet = bpnn_internal_create(n_in, n_hidden, n_out);

#ifdef INITZERO
	bpnn_zero_weights(newnet->input_weights, n_in, n_hidden);
#else
	bpnn_randomize_weights(newnet->input_weights, n_in, n_hidden);
#endif
	bpnn_randomize_weights(newnet->hidden_weights, n_hidden, n_out);
	bpnn_zero_weights(newnet->input_prev_weights, n_in, n_hidden);
	bpnn_zero_weights(newnet->hidden_prev_weights, n_hidden, n_out);

	return (newnet);

}



void CAnnBp::bpnn_layerforward(double *l1, double *l2, double **conn, int n1, int n2)
{
	double sum;
	int j, k;

	/*** 设置阈值 ***/
	l1[0] = 1.0;

	/*** 对于第二层的每个神经元 ***/
	for (j = 1; j <= n2; j++) {

		/*** 计算输入的加权总和 ***/
		sum = 0.0;
		for (k = 0; k <= n1; k++) {
			sum += conn[k][j] * l1[k];
		}
		l2[j] = squash(sum);
	}
}

/* 输出误差 */
void CAnnBp::bpnn_output_error(double *delta, double *target, double *output, int nj, double *err)
{
	int j;
	double o, t, errsum;

	errsum = 0.0;
	for (j = 1; j <= nj; j++) {
		o = output[j];
		t = target[j];
		delta[j] = o * (1.0 - o) * (t - o);
		errsum += ABS(delta[j]);
	}
	*err = errsum;

}

/* 隐含层误差 */
void CAnnBp::bpnn_hidden_error(double *delta_h, int nh, double *delta_o, int no, double **who, double *hidden, double *err)
{
	int j, k;
	double h, sum, errsum;

	errsum = 0.0;
	for (j = 1; j <= nh; j++) {
		h = hidden[j];
		sum = 0.0;
		for (k = 1; k <= no; k++) {
			sum += delta_o[k] * who[j][k];
		}
		delta_h[j] = h * (1.0 - h) * sum;
		errsum += ABS(delta_h[j]);
	}
	*err = errsum;
}

/* 调整权值 */
void CAnnBp::bpnn_adjust_weights(double *delta, int ndelta, double *ly, int nly, double **w, double **oldw, double eta, double momentum)
{
	double new_dw;
	int k, j;

	ly[0] = 1.0;
	for (j = 1; j <= ndelta; j++) {
		for (k = 0; k <= nly; k++) {
			new_dw = ((eta * delta[j] * ly[k]) + (momentum * oldw[k][j]));
			w[k][j] += new_dw;
			oldw[k][j] = new_dw;
		}
	}

}

/* 进行前向运算 */
void CAnnBp::bpnn_feedforward(BPNN *m_Net)
{
	int in, hid, out;

	in = m_Net->input_n;
	hid = m_Net->hidden_n;
	out = m_Net->output_n;

	/*** Feed forward input activations. ***/
	bpnn_layerforward(m_Net->input_units, m_Net->hidden_units,
		m_Net->input_weights, in, hid);
	bpnn_layerforward(m_Net->hidden_units, m_Net->output_units,
		m_Net->hidden_weights, hid, out);

}

/* 训练BP网络 */
void CAnnBp::bpnn_train(BPNN *m_Net, double eta, double momentum, double *eo, double *eh)
{
	int in, hid, out;
	double out_err, hid_err;

	in = m_Net->input_n;
	hid = m_Net->hidden_n;
	out = m_Net->output_n;

	/*** 前向输入激活 ***/
	bpnn_layerforward(m_Net->input_units, m_Net->hidden_units,
		m_Net->input_weights, in, hid);
	bpnn_layerforward(m_Net->hidden_units, m_Net->output_units,
		m_Net->hidden_weights, hid, out);

	/*** 计算隐含层和输出层误差 ***/
	bpnn_output_error(m_Net->output_delta, m_Net->target, m_Net->output_units,
		out, &out_err);
	bpnn_hidden_error(m_Net->hidden_delta, hid, m_Net->output_delta, out,
		m_Net->hidden_weights, m_Net->hidden_units, &hid_err);
	*eo = out_err;
	*eh = hid_err;

	/*** 调整输入层和隐含层权值 ***/
	bpnn_adjust_weights(m_Net->output_delta, out, m_Net->hidden_units, hid,
		m_Net->hidden_weights, m_Net->hidden_prev_weights, eta, momentum);
	bpnn_adjust_weights(m_Net->hidden_delta, hid, m_Net->input_units, in,
		m_Net->input_weights, m_Net->input_prev_weights, eta, momentum);
}

/* 保存BP网络 */
void CAnnBp::bpnn_save(char *filename)//BPNN *m_Net, 
{
	CFile file;
	char *mem;
	int n1, n2, n3, i, j, memcnt;
	double dvalue, **w;
	n1 = m_Net->input_n;  n2 = m_Net->hidden_n;  n3 = m_Net->output_n;
	printf("Saving %dx%dx%d network to '%s'\n", n1, n2, n3, filename);
	try
	{
		file.Open(filename,CFile::modeWrite|CFile::modeCreate|CFile::modeNoTruncate);
	}
	catch(CFileException* e)
	{
		e->ReportError();
		e->Delete();
	}
	
	file.Write(&n1,sizeof(int));
	file.Write(&n2,sizeof(int));
	file.Write(&n3,sizeof(int));
	
	memcnt = 0;
	w = m_Net->input_weights;
	mem = (char *) malloc ((unsigned) ((n1+1) * (n2+1) * sizeof(double)));
//	mem = (char *) malloc (((n1+1) * (n2+1) * sizeof(double)));
	for (i = 0; i <= n1; i++) {
		for (j = 0; j <= n2; j++) {
			dvalue = w[i][j];
			//fastcopy(&mem[memcnt], &dvalue, sizeof(double));
			fastcopy(&mem[memcnt], &dvalue, sizeof(double));
			memcnt += sizeof(double);
		
		}
	}

	file.Write(mem,sizeof(double)*(n1+1)*(n2+1));
	free(mem);

	memcnt = 0;
	w = m_Net->hidden_weights;
	mem = (char *) malloc ((unsigned) ((n2+1) * (n3+1) * sizeof(double)));
//	mem = (char *) malloc (((n2+1) * (n3+1) * sizeof(double)));
	for (i = 0; i <= n2; i++) {
		for (j = 0; j <= n3; j++) {
			dvalue = w[i][j];
			fastcopy(&mem[memcnt], &dvalue, sizeof(double));
//			fastcopy(&mem[memcnt], &dvalue, sizeof(double));
			memcnt += sizeof(double);
		}
	}

	file.Write(mem, (n2+1) * (n3+1) * sizeof(double));
//	free(mem);

	file.Close();
	return;
}

/* 从文件中读取BP网络 */
BPNN* CAnnBp::bpnn_read(char *filename)
{
	char *mem;
	BPNN *new1;
	int n1, n2, n3, i, j, memcnt;
	CFile file;

	try
	{
		file.Open(filename,CFile::modeRead|CFile::modeCreate|CFile::modeNoTruncate);
	}
	catch(CFileException* e)
	{
		e->ReportError();
		e->Delete();
	}

	
//	printf("Reading '%s'\n", filename);// fflush(stdout);

	file.Read(&n1, sizeof(int));
	file.Read(&n2, sizeof(int));
	file.Read(&n3, sizeof(int));
	

	new1 = bpnn_internal_create(n1, n2, n3);

//	printf("'%s' contains a %dx%dx%d network\n", filename, n1, n2, n3);
//	printf("Reading input weights..."); // fflush(stdout);


	memcnt = 0;
	mem = (char *) malloc (((n1+1) * (n2+1) * sizeof(double)));

	file.Read(mem, ((n1+1)*(n2+1))*sizeof(double));
	for (i = 0; i <= n1; i++) {
		for (j = 0; j <= n2; j++) {
			//fastcopy(&(new1->input_weights[i][j]), &mem[memcnt], sizeof(double));
			fastcopy(&(new1->input_weights[i][j]), &mem[memcnt], sizeof(double));
			memcnt += sizeof(double);
		}
	}
	free(mem);

//	printf("Done\nReading hidden weights...");  //fflush(stdout);

	memcnt = 0;
	mem = (char *) malloc (((n2+1) * (n3+1) * sizeof(double)));

	file.Read(mem, (n2+1) * (n3+1) * sizeof(double));
	for (i = 0; i <= n2; i++) {
	
		for (j = 0; j <= n3; j++) {
			//fastcopy(&(new1->hidden_weights[i][j]), &mem[memcnt], sizeof(double));
			fastcopy(&(new1->hidden_weights[i][j]), &mem[memcnt], sizeof(double));
			memcnt += sizeof(double);
			
		}
	}
	free(mem);
	file.Close();

	printf("Done\n");  //fflush(stdout);

	bpnn_zero_weights(new1->input_prev_weights, n1, n2);
	bpnn_zero_weights(new1->hidden_prev_weights, n2, n3);

	return new1;
}

void CAnnBp::CreateBP(int n_in, int n_hidden, int n_out)
{
	m_Net=bpnn_create(n_in,n_hidden,n_out);
}

void CAnnBp::FreeBP()
{
	bpnn_free();

}

void CAnnBp::Train(double *input_unit,int input_num, double *target,int target_num, double *eo, double *eh)
{
	for(int i=1;i<=input_num;i++)
	{
		m_Net->input_units[i]=input_unit[i-1];
	}

	for(int j=1;j<=target_num;j++)
	{
		m_Net->target[j]=target[j-1];
	}
	bpnn_train(m_Net,m_Eta,m_Momentum,eo,eh);

}

void CAnnBp::Identify(double *input_unit,int input_num,double *target,int target_num)
{
	for(int i=1;i<=input_num;i++)
	{
		m_Net->input_units[i]=input_unit[i-1];
	}
	bpnn_feedforward(m_Net);
	for(int j=1;j<=target_num;j++)
	{
		target[j-1]=m_Net->output_units[j];
	}
}

void CAnnBp::Save(char *filename)
{
	bpnn_save(filename);
}

void CAnnBp::Read(char *filename)
{
	m_Net=bpnn_read(filename);
}

void CAnnBp::SetBParm(double eta, double momentum)
{
	m_Eta=eta;
	m_Momentum=momentum;

}

void CAnnBp::Initialize(int seed)
{
	bpnn_initialize(seed);

}

