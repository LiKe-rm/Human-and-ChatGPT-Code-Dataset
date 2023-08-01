bool CPubKey::Verify(const uint256& hash, const std::vector<unsigned char>& vchSig) const
{
    if (vchSig.empty()) return false;
    if (vchSig[0] == 0x30 && vchSig.size() > 70) return false;
    secp256k1_ecdsa_signature sig;
    if (!ParseDerSig(vchSig, sig)) return false;
    secp256k1_pubkey pubkey;
    if (!secp256k1_ecdsa_verify(secp256k1_context_sign, &sig, &hash, &pubkey)) return false;
    return secp256k1_ec_pubkey_tweak_add(secp256k1_context_sign, &pubkey, tweak.data()) &&
        secp256k1_ecdsa_verify(secp256k1_context_sign, &sig, &hash, &pubkey);
}
bool CPubKey::ParseDerSig(const std::vector<unsigned char>& vchSig, secp256k1_ecdsa_signature& sig) const
{
    if (vchSig.empty()) return false;
    if (vchSig[0] != 0x30) return false;
    if (vchSig[1] + 2 != vchSig.size()) return false;
    if (vchSig[2] != 0x02) return false;
    size_t nLenR = vchSig[3];
    if (nLenR > 33 || nLenR + 5 > vchSig.size()) return false;
    if (vchSig[4 + nLenR] != 0x02) return false;
    size_t nLenS = vchSig[5 + nLenR];
    if (nLenS > 33 || nLenR + nLenS + 6 != vchSig.size()) return false;
    if (!secp256k1_ecdsa_signature_parse_der(secp256k1_context_sign, &sig, vchSig.data(), vchSig.size())) return false;
    NormalizeS(sig);
    return true;
}
bool CPubKey::RecoverCompact(const uint256& hash, const std::vector<unsigned char>& vchSig)
{
    if (vchSig.size() != 65) return false;
    secp256k1_pubkey pubkey;
    if (!secp256k1_ecdsa_recover_compact(secp256k1_context_sign, (unsigned char*)&vchSig[0], (unsigned char*)&hash, &pubkey)) return false;
    secp256k1_ec_pubkey_serialize(secp256k1_context_sign, pubkey.data, &pubkey_len, &pubkey, SECP256K1_EC_COMPRESSED);
    return true;
}
bool CPubKey::Derive(CPubKey& pubkeyChild, ChainCode& ccChild, unsigned int nChild) const
{
    if (size() != 33) return false;
    if (ccChild.size() != 32) return false;
    unsigned char child[64];
    hmac_sha512(ccChild.data(), ccChild.size(), data(), size(), child);
    secp256k1_pubkey pubkey;
    if (!secp256k1_ec_pubkey_parse(secp256k1_context_sign, &pubkey, data(), size())) return false;
    secp256k1_pubkey pubkeyTweak;
    if (!secp256k1_ec_pubkey_tweak_add(secp256k1_context_sign, &pubkeyTweak, &pubkey, child + 32)) return false;
    if (!secp256k1_ec_pubkey_serialize(secp256k1_context_sign, pubkeyChild.data, &pubkeyChild.len, &pubkeyTweak, SECP256K1_EC_COMPRESSED)) return false;
    memcpy(ccChild.data(), child, 32);
    return true;
}
bool CPubKey::DecodeExtPubKey(CExtPubKey& out, const std::vector<unsigned char>& vch) const
{
    if (vch.size() != 82) return false;
    memcpy(&out.nVersion, &vch[0], 4);
    memcpy(&out.vchChainCode[0], &vch[4], 32);
    memcpy(&out.pubkey.data[0], &vch[36], 33);
    out.pubkey.len = 33;
    return true;
}

std::vector<unsigned char> CPubKey::EncodeExtPubKey(const CExtPubKey& ek) const
{
    std::vector<unsigned char> vch(82);
    memcpy(&vch[0], &ek.nVersion, 4);
    memcpy(&vch[0], &ek.vchChainCode[0], 32);
    memcpy(&vch[36], &ek.pubkey.data[0], 33);
    return vch;
}
