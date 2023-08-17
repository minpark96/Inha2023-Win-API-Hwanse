#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;

	Vec2		m_vForce;	// ũ��, ����
	Vec2		m_vAccel;	// ���ӵ�
	Vec2		m_vVelocity; // �ӵ�( ũ�� : �ӷ�, ����)
	float		m_fMass;	// ����

	// F = M * A;
	// V += A * DT

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

