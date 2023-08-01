package com.example.cryptopp;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Arrays;

public class PKCS {
    public static final int MAX_UNPADDED_LENGTH = 10;

    public static byte[] pad(byte[] input, int paddedLength) {
        if (input.length > maxUnpaddedLength(paddedLength)) {
            throw new IllegalArgumentException("Input length is too large");
        }

        byte[] pkcsBlock = new byte[paddedLength];
        SecureRandom rng = new SecureRandom();
        pkcsBlock[0] = 2;

        for (int i = 1; i < paddedLength - input.length - 1; i++) {
            int randomByte;
            do {
                randomByte = rng.nextInt(256);
            } while (randomByte == 0);
            pkcsBlock[i] = (byte) randomByte;
        }

        pkcsBlock[paddedLength - input.length - 1] = 0;
        System.arraycopy(input, 0, pkcsBlock, paddedLength - input.length, input.length);
        return pkcsBlock;
    }

    public static byte[] unpad(byte[] pkcsBlock) {
        if (pkcsBlock[0] != 2) {
            throw new IllegalArgumentException("Invalid padding");
        }

        int separatorIndex = -1;
        for (int i = 1; i < pkcsBlock.length; i++) {
            if (pkcsBlock[i] == 0) {
                separatorIndex = i;
                break;
            }
        }

        if (separatorIndex == -1) {
            throw new IllegalArgumentException("Invalid padding");
        }

        return Arrays.copyOfRange(pkcsBlock, separatorIndex + 1, pkcsBlock.length);
    }

    public static int maxUnpaddedLength(int paddedLength) {
        return paddedLength - MAX_UNPADDED_LENGTH;
    }

    public static byte[] computeMessageRepresentative(byte[] message, String hashAlgorithm) {
        try {
            MessageDigest md = MessageDigest.getInstance(hashAlgorithm);
            byte[] digest = md.digest(message);
            byte[] representative = new byte[digest.length + MAX_UNPADDED_LENGTH];

            representative[0] = 1;
            Arrays.fill(representative, 1, representative.length - digest.length - 1, (byte) 0xff);
            representative[representative.length - digest.length - 1] = 0;
            System.arraycopy(digest, 0, representative, representative.length - digest.length, digest.length);

            return representative;
        } catch (NoSuchAlgorithmException e) {
            throw new IllegalArgumentException("Invalid hash algorithm", e);
        }
    }
}
