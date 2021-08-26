#include "Matrix4x4.h"
using namespace My;

Matrix4x4 Matrix4x4::identity = Matrix4x4(
									Vector4(1, 0, 0, 0),
									Vector4(0, 1, 0, 0),
									Vector4(0, 0, 1, 0),
									Vector4(0, 0, 0, 1));

Matrix4x4 Matrix4x4::zero = Matrix4x4(
									Vector4(0, 0, 0, 0),
									Vector4(0, 0, 0, 0),
									Vector4(0, 0, 0, 0),
									Vector4(0, 0, 0, 0));

Matrix4x4 Matrix4x4::transpose() 
{
	return Matrix4x4(
				Vector4(m00, m01, m02, m03),
				Vector4(m10, m11, m12, m13),
				Vector4(m20, m21, m22, m23),
				Vector4(m30, m31, m32, m33));
} 

Vector3 Matrix4x4::lossyScale() 
{
	return Vector3(m00, m11, m22);
}

Matrix4x4::Matrix4x4() {
	m00 = 0.0f;
	m01 = 0.0f;
	m02 = 0.0f;
	m03 = 0.0f;
	m10 = 0.0f;
	m11 = 0.0f;
	m12 = 0.0f;
	m13 = 0.0f;
	m20 = 0.0f;
	m21 = 0.0f;
	m22 = 0.0f;
	m23 = 0.0f;
	m30 = 0.0f;
	m31 = 0.0f;
	m32 = 0.0f;
	m33 = 0.0f;
}

Matrix4x4::Matrix4x4(Vector4 column0, Vector4 column1, Vector4 column2, Vector4 column3)
{
	m00 = column0.x;
	m01 = column1.x;
	m02 = column2.x;
	m03 = column3.x;
	m10 = column0.y;
	m11 = column1.y;
	m12 = column2.y;
	m13 = column3.y;
	m20 = column0.z;
	m21 = column1.z;
	m22 = column2.z;
	m23 = column3.z;
	m30 = column0.w;
	m31 = column1.w;
	m32 = column2.w;
	m33 = column3.w;
}

Matrix4x4::Matrix4x4(const Matrix4x4& matrix)
{
	m00 = matrix.m00;
	m01 = matrix.m01;
	m02 = matrix.m02;
	m03 = matrix.m03;
	m10 = matrix.m10;
	m11 = matrix.m11;
	m12 = matrix.m12;
	m13 = matrix.m13;
	m20 = matrix.m20;
	m21 = matrix.m21;
	m22 = matrix.m22;
	m23 = matrix.m23;
	m30 = matrix.m30;
	m31 = matrix.m31;
	m32 = matrix.m32;
	m33 = matrix.m33;
}

Vector4 Matrix4x4::GetColumn(int index)
{
	switch (index)
	{
	case 0:
		return Vector4(m00, m10, m20, m30);
		break;
	case 1:
		return Vector4(m01, m11, m21, m31);
		break;
	case 2:
		return Vector4(m02, m12, m22, m23);
		break;
	case 3:
		return Vector4(m03, m13, m23, m33);
		break;
	default:
		throw "Out of range: Use 0, 1, 2 or 3";
		break;
	}
}

Vector4 Matrix4x4::GetRow(int index)
{
	switch (index)
	{
	case 0:
		return Vector4(m00, m01, m02, m03);
		break;
	case 1:
		return Vector4(m10, m11, m12, m13);
		break;
	case 2:
		return Vector4(m20, m21, m22, m23);
		break;
	case 3:
		return Vector4(m30, m31, m32, m33);
		break;
	default:
		throw "Out of range: Use 0, 1, 2 or 3";
		break;
	}
}

void Matrix4x4::SetColumn(int index, Vector4 column)
{
	switch (index)
	{
	case 0:
		m00 = column.x;
		m10 = column.y;
		m20 = column.z;
		m30 = column.w;
		break;
	case 1:
		m01 = column.x;
		m11 = column.y;
		m21 = column.z;
		m31 = column.w;
		break;
	case 2:
		m02 = column.x;
		m12 = column.y;
		m22 = column.z;
		m32 = column.w;
		break;
	case 3:
		m03 = column.x;
		m13 = column.y;
		m23 = column.z;
		m33 = column.w;
		break;
	default:
		throw "Out of range: Use 0, 1, 2 or 3";
		break;
	}
}

void Matrix4x4::SetRow(int index, Vector4 row)
{
	switch (index) {
	case 0:
		m00 = row.x;
		m01 = row.y;
		m02 = row.z;
		m03 = row.w;
		break;
	case 1:
		m10 = row.x;
		m11 = row.y;
		m12 = row.z;
		m13 = row.w;
		break;
	case 2:
		m20 = row.x;
		m21 = row.y;
		m22 = row.z;
		m23 = row.w;
		break;
	case 3:
		m30 = row.x;
		m31 = row.y;
		m32 = row.z;
		m33 = row.w;
		break;
	default:
		throw "Out of range: Use 0, 1, 2 or 3";
		break;
	}
}

void Matrix4x4::TRS(Vector3 position, Quaternion rotation, Vector3 scale)
{
	Translate(position);
	Rotate(rotation);
	Scale(scale);
}

void Matrix4x4::Translate(Vector3 translate) 
{
	this->m03 += translate.x;
	this->m13 += translate.y;
	this->m23 += translate.z;
	this->m33 = 1;
}

void Matrix4x4::Scale(Vector3 scale)
{
	this->m00 *= scale.x;
	this->m11 *= scale.y;
	this->m22 *= scale.z;
	this->m33 = 1;
}

void Matrix4x4::Rotate(Quaternion quaternion)
{
	this->m02 = 2.0f * (quaternion.x * quaternion.z) + 2.0f * (quaternion.y * quaternion.w);
	this->m12 = 2.0f * (quaternion.y * quaternion.z) - 2.0f * (quaternion.x * quaternion.w);
	this->m22 = 1 - 2.0f * (quaternion.x * quaternion.x) - 2.0f * (quaternion.y * quaternion.y);
	
	this->m00 = 1 - 2.0f * (quaternion.y * quaternion.y) - 2.0f * (quaternion.z * quaternion.z);
	this->m10 = 2.0f * (quaternion.x * quaternion.y) + 2.0f * (quaternion.z * quaternion.w);
	this->m20 = 2.0f * (quaternion.x * quaternion.z) - 2.0f * (quaternion.y * quaternion.w);
	
	this->m01 = 2.0f * (quaternion.x * quaternion.y) - 2.0f * (quaternion.z * quaternion.w);
	this->m11 = 1 - 2.0f * (quaternion.x * quaternion.x) - 2.0f * (quaternion.z * quaternion.z);
	this->m21 = 2.0f * (quaternion.y * quaternion.z) + 2.0f * (quaternion.x * quaternion.w);
}

Matrix4x4 Matrix4x4::Rotate(Matrix4x4 matrix, Quaternion quaternion)
{
	matrix.m02 = 2.0f * (quaternion.x * quaternion.z) + 2.0f * (quaternion.y * quaternion.w);
	matrix.m12 = 2.0f * (quaternion.y * quaternion.z) - 2.0f * (quaternion.x * quaternion.w);
	matrix.m22 = 1 - 2.0f * (quaternion.x * quaternion.x) - 2.0f * (quaternion.y * quaternion.y);

	matrix.m00 = 1 - 2.0f * (quaternion.y * quaternion.y) - 2.0f * (quaternion.z * quaternion.z);
	matrix.m10 = 2.0f * (quaternion.x * quaternion.y) + 2.0f * (quaternion.z * quaternion.w);
	matrix.m20 = 2.0f * (quaternion.x * quaternion.z) - 2.0f * (quaternion.y * quaternion.w);

	matrix.m01 = 2.0f * (quaternion.x * quaternion.y) - 2.0f * (quaternion.z * quaternion.w);
	matrix.m11 = 1 - 2.0f * (quaternion.x * quaternion.x) - 2.0f * (quaternion.z * quaternion.z);
	matrix.m21 = 2.0f * (quaternion.y * quaternion.z) + 2.0f * (quaternion.x * quaternion.w);
	return matrix;
}

Matrix4x4 Matrix4x4::Scale(Matrix4x4 matrix, Vector3 scale)
{
	matrix.m00 *= scale.x;
	matrix.m11 *= scale.y;
	matrix.m22 *= scale.z;
	matrix.m33 = 1;
	return matrix;
}

Matrix4x4 Matrix4x4::Translate(Matrix4x4 matrix, Vector3 translate)
{
	matrix.m03 += translate.x;
	matrix.m13 += translate.y;
	matrix.m23 += translate.z;
	matrix.m33 = 1;
	return matrix;
}

Matrix4x4 Matrix4x4::TRS(Matrix4x4 matrix, Matrix4x4 translate, Matrix4x4 rotate, Matrix4x4 scale)
{
	matrix = translate * rotate * scale;
	return matrix;
}

Matrix4x4 Matrix4x4::TRS(Matrix4x4 translate, Matrix4x4 rotate, Matrix4x4 scale, Vector3 position, Quaternion rotation, Vector3 scalar)
{
	translate = Translate(translate, position);
	rotate = Rotate(rotate, rotation);
	scale = Scale(scale, scalar);
	Matrix4x4 trs = translate * rotate * scale;
	return trs;
}

Vector4 My::operator*(Matrix4x4 a, Vector4 vector)
{
	Vector4 newVec4 = Vector4::zero;
	newVec4.x = (a.m00 * vector.x) + (a.m01 * vector.y) + (a.m02 * vector.z) + (a.m03 * vector.w);
	newVec4.y = (a.m10 * vector.x) + (a.m11 * vector.y) + (a.m12 * vector.z) + (a.m13 * vector.w);
	newVec4.z = (a.m20 * vector.x) + (a.m21 * vector.y) + (a.m22 * vector.z) + (a.m23 * vector.w);
	newVec4.w = (a.m30 * vector.x) + (a.m31 * vector.y) + (a.m32 * vector.z) + (a.m33 * vector.w);
	return newVec4;
}

Matrix4x4 My::operator*(Matrix4x4 a, Matrix4x4 b)
{
	Matrix4x4 matXMat = Matrix4x4::zero;
	matXMat.m00 = (a.m00 * b.m00) + (a.m01 * b.m10) + (a.m02 * b.m20) + (a.m03 * b.m30);
	matXMat.m01 = (a.m00 * b.m01) + (a.m01 * b.m11) + (a.m02 * b.m21) + (a.m03 * b.m31);
	matXMat.m02 = (a.m00 * b.m02) + (a.m01 * b.m12) + (a.m02 * b.m22) + (a.m03 * b.m32);
	matXMat.m03 = (a.m00 * b.m03) + (a.m01 * b.m13) + (a.m02 * b.m23) + (a.m03 * b.m33);

	matXMat.m10 = (a.m10 * b.m00) + (a.m11 * b.m10) + (a.m12 * b.m20) + (a.m13 * b.m30);
	matXMat.m11 = (a.m10 * b.m01) + (a.m11 * b.m11) + (a.m12 * b.m21) + (a.m13 * b.m31);
	matXMat.m12 = (a.m10 * b.m02) + (a.m11 * b.m12) + (a.m12 * b.m22) + (a.m13 * b.m32);
	matXMat.m13 = (a.m10 * b.m03) + (a.m11 * b.m13) + (a.m12 * b.m23) + (a.m13 * b.m33);

	matXMat.m20 = (a.m20 * b.m00) + (a.m21 * b.m10) + (a.m22 * b.m20) + (a.m23 * b.m30);
	matXMat.m21 = (a.m20 * b.m01) + (a.m21 * b.m11) + (a.m22 * b.m21) + (a.m23 * b.m31);
	matXMat.m22 = (a.m20 * b.m02) + (a.m21 * b.m12) + (a.m22 * b.m22) + (a.m23 * b.m32);
	matXMat.m23 = (a.m20 * b.m03) + (a.m21 * b.m13) + (a.m22 * b.m23) + (a.m23 * b.m33);

	matXMat.m30 = (a.m30 * b.m00) + (a.m31 * b.m10) + (a.m32 * b.m20) + (a.m33 * b.m30);
	matXMat.m31 = (a.m30 * b.m01) + (a.m31 * b.m11) + (a.m32 * b.m21) + (a.m33 * b.m31);
	matXMat.m32 = (a.m30 * b.m02) + (a.m31 * b.m12) + (a.m32 * b.m22) + (a.m33 * b.m32);
	matXMat.m33 = (a.m30 * b.m03) + (a.m31 * b.m13) + (a.m32 * b.m23) + (a.m33 * b.m33);
	return matXMat;
}

bool My::operator==(Matrix4x4 a, Matrix4x4 b)
{
	return (a.m00 == b.m00 && a.m01 == b.m01 && a.m02 == b.m02 && a.m03 == b.m03 &&
		a.m10 == b.m10 && a.m11 == b.m11 && a.m12 == b.m12 && a.m13 == b.m13 &&
		a.m20 == b.m20 && a.m21 == b.m21 && a.m22 == b.m22 && a.m23 == b.m23 &&
		a.m30 == b.m30 && a.m31 == b.m31 && a.m32 == b.m32 && a.m33 == b.m33);
}

bool My::operator!=(Matrix4x4 a, Matrix4x4 b)
{
	return !(a == b);
}