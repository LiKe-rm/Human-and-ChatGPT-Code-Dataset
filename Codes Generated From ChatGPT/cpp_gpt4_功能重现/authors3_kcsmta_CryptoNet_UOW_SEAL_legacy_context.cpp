#include <iostream>
#include <memory>
#include <vector>
#include "seal/encryptionparams.h"
#include "seal/util/ntt.h"
#include "seal/util/polyarithsmallmod.h"
#include "seal/util/uintarith.h"
#include "seal/util/uintcore.h"

namespace seal {
    class SEALContext {
    public:
        SEALContext(const EncryptionParameters &params);

        const EncryptionParameters &context_params() const;
        const EncryptionParameterQualifiers &context_qualifiers() const;

        const std::vector<std::shared_ptr<util::NTTTables>> &ntt_tables() const;
        const std::vector<std::shared_ptr<util::NTTTables>> &plain_ntt_tables() const;

        bool validate();

    private:
        void precompute_ntt_tables();
        void precompute_plain_ntt_tables();

        EncryptionParameters params_;
        EncryptionParameterQualifiers qualifiers_;
        std::vector<std::shared_ptr<util::NTTTables>> ntt_tables_;
        std::vector<std::shared_ptr<util::NTTTables>> plain_ntt_tables_;
    };

    SEALContext::SEALContext(const EncryptionParameters &params) : params_(params) {
        validate();
        precompute_ntt_tables();
        precompute_plain_ntt_tables();
    }

    const EncryptionParameters &SEALContext::context_params() const {
        return params_;
    }

    const EncryptionParameterQualifiers &SEALContext::context_qualifiers() const {
        return qualifiers_;
    }

    const std::vector<std::shared_ptr<util::NTTTables>> &SEALContext::ntt_tables() const {
        return ntt_tables_;
    }

    const std::vector<std::shared_ptr<util::NTTTables>> &SEALContext::plain_ntt_tables() const {
        return plain_ntt_tables_;
    }

    bool SEALContext::validate() {
        // Validate EncryptionParameters and generate EncryptionParameterQualifiers
        // (e.g., NTT support, batching support, relinearization support, etc.)
        // Implementation of this function depends on the specific encryption scheme.
        // Please refer to the SEAL library for the actual implementation.
        return true;
    }

    void SEALContext::precompute_ntt_tables() {
        // Precompute NTT tables for coeff_modulus
        size_t coeff_modulus_size = params_.coeff_modulus().size();
        ntt_tables_.resize(coeff_modulus_size);
        for (size_t i = 0; i < coeff_modulus_size; i++) {
            ntt_tables_[i] = std::make_shared<util::NTTTables>(params_.poly_modulus_degree(), params_.coeff_modulus()[i]);
        }
    }

    void SEALContext::precompute_plain_ntt_tables() {
        // Precompute NTT tables for plain_modulus
        plain_ntt_tables_.resize(1);
        plain_ntt_tables_[0] = std::make_shared<util::NTTTables>(params_.poly_modulus_degree(), params_.plain_modulus());
    }
}
