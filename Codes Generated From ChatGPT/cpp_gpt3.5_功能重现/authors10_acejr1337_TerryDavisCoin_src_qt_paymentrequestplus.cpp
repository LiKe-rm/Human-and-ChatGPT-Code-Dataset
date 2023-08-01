#include <iostream>
#include <string>
#include <vector>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <google/protobuf/message_lite.h>
#include "payment_request.pb.h"

using namespace std;
using namespace google::protobuf;

class PaymentRequestWrapper {
    public:
    PaymentRequestWrapper() {
        SSL_library_init();
        SSL_load_error_strings();
        OpenSSL_add_all_algorithms();
    }

    ~PaymentRequestWrapper() {
        EVP_cleanup();
    }

    bool ParseFromString(const string& data) {
        PaymentRequest request;
        if (!request.ParseFromString(data)) {
            cerr << "Failed to parse PaymentRequest." << endl;
            return false;
        }
        request_ = request;
        return true;
    }

    string SerializeAsString() const {
        return request_.SerializeAsString();
    }

    string GetMerchantInfo() const {
        return request_.merchant_info();
    }

    double GetPaymentAmount() const {
        return request_.payment_amount();
    }

    bool VerifySignature(const string& signature, const string& cert_data) {
        X509* cert = nullptr;
        BIO* bio = nullptr;
        EVP_PKEY* pubkey = nullptr;
        bool ret = false;

        do {
            // Load certificate
            bio = BIO_new_mem_buf(cert_data.c_str(), cert_data.length());
            if (!bio) {
                cerr << "Failed to create BIO for certificate." << endl;
                break;
            }
            cert = PEM_read_bio_X509(bio, nullptr, nullptr, nullptr);
            if (!cert) {
                cerr << "Failed to read X509 certificate from BIO." << endl;
                break;
            }

            // Load public key from certificate
            pubkey = X509_get_pubkey(cert);
            if (!pubkey) {
                cerr << "Failed to get public key from certificate." << endl;
                break;
            }

            // Verify signature
            const EVP_MD* md = EVP_get_digestbyname("SHA256");
            if (!md) {
                cerr << "Failed to get digest for signature verification." << endl;
                break;
            }
            EVP_MD_CTX* ctx = EVP_MD_CTX_new();
            if (!ctx) {
                cerr << "Failed to create EVP_MD_CTX for signature verification." << endl;
                break;
            }
            if (!EVP_VerifyInit(ctx, md)) {
                cerr << "Failed to initialize signature verification." << endl;
                break;
            }
            if (!EVP_VerifyUpdate(ctx, request_.SerializeAsString().c_str(), request_.ByteSizeLong())) {
                cerr << "Failed to update signature verification." << endl;
                break;
            }
            if (EVP_VerifyFinal(ctx, (const unsigned char*)signature.c_str(), signature.length(), pubkey) != 1) {
                cerr << "Signature verification failed." << endl;
                break;
            }

            ret = true;
        } while (0);

        if (pubkey) {
            EVP_PKEY_free(pubkey);
        }
        if (cert#include <iostream>
#include <string>
#include <vector>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <google/protobuf/message_lite.h>
#include "payment_request.pb.h"

            using namespace std;
            using namespace google::protobuf;

            class PaymentRequestWrapper {
                public:
                PaymentRequestWrapper() {
                    SSL_library_init();
                    SSL_load_error_strings();
                    OpenSSL_add_all_algorithms();
                }

                ~PaymentRequestWrapper() {
                    EVP_cleanup();
                }

                bool ParseFromString(const string& data) {
                    PaymentRequest request;
                    if (!request.ParseFromString(data)) {
                        cerr << "Failed to parse PaymentRequest." << endl;
                        return false;
                    }
                    request_ = request;
                    return true;
                }

                string SerializeAsString() const {
                    return request_.SerializeAsString();
                }

                string GetMerchantInfo() const {
                    return request_.merchant_info();
                }

                double GetPaymentAmount() const {
                    return request_.payment_amount();
                }

                bool VerifySignature(const string& signature, const string& cert_data) {
                    X509* cert = nullptr;
                    BIO* bio = nullptr;
                    EVP_PKEY* pubkey = nullptr;
                    bool ret = false;

                    do {
                        // Load certificate
                        bio = BIO_new_mem_buf(cert_data.c_str(), cert_data.length());
                        if (!bio) {
                            cerr << "Failed to create BIO for certificate." << endl;
                            break;
                        }
                        cert = PEM_read_bio_X509(bio, nullptr, nullptr, nullptr);
                        if (!cert) {
                            cerr << "Failed to read X509 certificate from BIO." << endl;
                            break;
                        }

                        // Load public key from certificate
                        pubkey = X509_get_pubkey(cert);
                        if (!pubkey) {
                            cerr << "Failed to get public key from certificate." << endl;
                            break;
                        }

                        // Verify signature
                        const EVP_MD* md = EVP_get_digestbyname("SHA256");
                        if (!md) {
                            cerr << "Failed to get digest for signature verification." << endl;
                            break;
                        }
                        EVP_MD_CTX* ctx = EVP_MD_CTX_new();
                        if (!ctx) {
                            cerr << "Failed to create EVP_MD_CTX for signature verification." << endl;
                            break;
                        }
                        if (!EVP_VerifyInit(ctx, md)) {
                            cerr << "Failed to initialize signature verification." << endl;
                            break;
                        }
                        if (!EVP_VerifyUpdate(ctx, request_.SerializeAsString().c_str(), request_.ByteSizeLong())) {
                            cerr << "Failed to update signature verification." << endl;
                            break;
                        }
                        if (EVP_VerifyFinal(ctx, (const unsigned char*)signature.c_str(), signature.length(), pubkey) != 1) {
                            cerr << "Signature verification failed." << endl;
                            break;
                        }

                        ret = true;
                    } while (0);

                    if (pubkey) {
                        EVP_PKEY_free(pubkey);
                    }
                    if (cert) {
                        X509_free(cert);
                    }
                    if (bio) {
                        BIO_free(bio);
                    }
                    return ret;
                }

                bool VerifyCertificate(const string& cert_data) {
                    X509* cert = nullptr;
                    BIO* bio = nullptr;
                    bool ret = false;

                    do {
                        // Load certificate
                        bio = BIO_new_mem_buf(cert_data.c_str(), cert_data.length());
                        if (!bio) {
                            cerr << "Failed to create BIO for certificate." << endl;
                            break;
                        }
                        cert = PEM_read_bio_X509(bio, nullptr, nullptr, nullptr);
                        if (!cert) {
                            cerr << "Failed to read X509 certificate from BIO." << endl;
                            break;
                        }

                        // Verify validity period
                        time_t now = time(nullptr);
                        if (now < X509_get_notBefore(cert) || now > X509_get_notAfter(cert)) {
                            cerr << "Certificate is expired or not yet valid." << endl;
                            break;
                        }

                        ret = true;
                    } while (0);

                    if (cert) {
                        X509_free(cert);
                    }
                    if (bio) {
                        BIO_free(bio);
                    }

                    return ret;
                }
                private:
                PaymentRequest request_;
        };

        int main() {
            PaymentRequestWrapper wrapper;
            // Parse payment request from string
            string payment_request_data = "..."; // Payment request data in binary format
            if (!wrapper.ParseFromString(payment_request_data)) {
                cerr << "Failed to parse payment request." << endl;
                return 1;
            }

            // Serialize payment request to string
            string serialized_data = wrapper.SerializeAsString();
            cout << "Serialized payment request data: " << serialized_data << endl;

            // Get merchant info and payment amount
            string merchant_info = wrapper.GetMerchantInfo();
            double payment_amount = wrapper.GetPaymentAmount();
            cout << "Merchant info: " << merchant_info << endl;
            cout << "Payment amount: " << payment_amount << endl;

            // Verify signature and certificate
            string signature = "..."; // Payment request signature in binary format
            string certificate_data = "..."; // X509 certificate data in PEM format
            if (!wrapper.VerifySignature(signature, certificate_data)) {
                cerr << "Failed to verify payment request signature." << endl;
                return 1;
            }
            if (!wrapper.VerifyCertificate(certificate_data)) {
                cerr << "Failed to verify payment request certificate." << endl;
                return 1;
            }

            return 0;
        }