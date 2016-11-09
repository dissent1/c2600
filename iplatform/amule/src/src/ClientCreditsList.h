//
// This file is part of the aMule Project.
//
// Copyright (c) 2003-2011 aMule Team ( admin@amule.org / http://www.amule.org )
// Copyright (c) 2002-2011 Merkur ( devs@emule-project.net / http://www.emule-project.net )
//
// Any parts of this program derived from the xMule, lMule or eMule project,
// or contributed by third-party developers are copyrighted by their
// respective authors.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301, USA
//

#ifndef CLIENTCREDITSLIST_H
#define CLIENTCREDITSLIST_H

#include "MD4Hash.h"	// Needed for CMD4Hash

#include <map>

class CClientCredits;

class CClientCreditsList
{
public:
	CClientCreditsList();
	~CClientCreditsList();
	
	// return signature size, 0 = Failed | use sigkey param for debug only
	uint8	CreateSignature(CClientCredits* pTarget, byte* pachOutput, uint8 nMaxSize, uint32 ChallengeIP, uint8 byChaIPKind, void* sigkey = NULL);
	bool	VerifyIdent(CClientCredits* pTarget, const byte* pachSignature, uint8 nInputSize, uint32 dwForIP, uint8 byChaIPKind);	

	CClientCredits* GetCredit(const CMD4Hash& key);
	void	Process();
	uint8	GetPubKeyLen() const 			{return m_nMyPublicKeyLen;}
	const byte*	GetPublicKey() const		{return m_abyMyPublicKey;}
	bool	CryptoAvailable() const;
	void	SaveList();
	void	PrintClientCreditsList();
	uint32	GetMapClientSize() {return m_mapClients.size();}
protected:
	void	LoadList();
	void	InitalizeCrypting();
	bool	CreateKeyPair();
#ifdef _DEBUG
	bool	Debug_CheckCrypting();
#endif
private:
	typedef std::map<CMD4Hash, CClientCredits*> ClientMap;
	ClientMap	m_mapClients;
	uint32		m_nLastSaved;
	// A void* to avoid having to include the large CryptoPP.h file
#ifndef ENABLE_TOMCRYPT
	void*		m_pSignkey;
#else
	byte		m_abyMySignKey[MAX_CLIENT_SIGN_KEY_LEN]; //512 enough when 384bits key size
	uint16		m_nMySignKeyLen;
#endif //ENABLE_TOMCRYPT
	byte		m_abyMyPublicKey[MAX_CLIENT_PUB_KEY_LEN];
	uint8		m_nMyPublicKeyLen;
};

#endif // CLIENTCREDITSLIST_H
// File_checked_for_headers
