#ifndef ROOT_CERTIFICATES_HPP
#define ROOT_CERTIFICATES_HPP

#include <boost/asio/ssl.hpp>
#include <string>

// Function to load root certificates into the SSL context
inline void load_root_certificates(boost::asio::ssl::context& ctx)
{
    std::string const cert =
        "-----BEGIN CERTIFICATE-----\n"
        "MIIDnzCCAoegAwIBAgIUTTAvm/eYGr+zrVKD0EA71KKdlGowDQYJKoZIhvcNAQEL\n"
        "BQAwXzELMAkGA1UEBhMCSU4xDjAMBgNVBAgMBUJpaGFyMQ8wDQYDVQQHDAZHb3Jh\n"
        "cmkxDTALBgNVBAoMBEtQSVQxDDAKBgNVBAsMA1ZOQTESMBAGA1UEAwwJMTI3LjAu\n"
        "MC4xMB4XDTI0MTIxOTE2NTExNFoXDTI1MTIxOTE2NTExNFowXzELMAkGA1UEBhMC\n"
        "SU4xDjAMBgNVBAgMBUJpaGFyMQ8wDQYDVQQHDAZHb3JhcmkxDTALBgNVBAoMBEtQ\n"
        "SVQxDDAKBgNVBAsMA1ZOQTESMBAGA1UEAwwJMTI3LjAuMC4xMIIBIjANBgkqhkiG\n"
        "9w0BAQEFAAOCAQ8AMIIBCgKCAQEAyzHx/TMEz5aDDDqWYXk8bMZk4ckxo1vt02Zg\n"
        "kHD3dWoSsq86zzZs3S1UPpYwzd7yHNWvs4ggf1qJHlXNkvUeh0Au8BpaX9q7ctPV\n"
        "08Z5pCPORxgmoZ5jB+7UPRao5g5lDW0T9CkioQ43zRYrc2nt7c0JkFpFlsTpy910\n"
        "Js77NnsAgHVF+ZIpVItg2pEllrJiukVr7O73+/PrgLEbGyFRrYyuj9BP9vgn7Sfr\n"
        "bGqFy3Zrc1mNQjMiiFsx8j7En1NcVKq9cmvhs4spA9wXRMZQ0MpSWQfb1hKOmUY5\n"
        "fUVF2AjeYkGY+35xVrOYnBChoDrj9YpsI+NgGezF5bNamdv0AQIDAQABo1MwUTAd\n"
        "BgNVHQ4EFgQUwqkFaISmMBtMhtimxSo1wUGjfZowHwYDVR0jBBgwFoAUwqkFaISm\n"
        "MBtMhtimxSo1wUGjfZowDwYDVR0TAQH/BAUwAwEB/zANBgkqhkiG9w0BAQsFAAOC\n"
        "AQEAf+ZcbqRrLqz+J6XJCG77ifNmzW+mQBtiiiuY85B7/X9znTmRkDNV53bA9im0\n"
        "X6doTGXZIGgzSB0Kl/hgk0wp42slRmgYDKUsIUBjCiTzuSUBjmfU04XlBwwTTpri\n"
        "9KOiXd9q6lBM/3kDFfhruHY6s895kKqNzTVb1yDAihLjNUut3kiEh23nfLU49rtk\n"
        "SYcFpb9XEsy6lFiph5jQcD2no0TjOdpLCi45IE3SNddhgLmVEz/ODF22ZytqNXmz\n"
        "7q/bVtcHeQOzYE0yuOIRw9C1T3t7BXF5vvhP1x0/TFI6P9WV+8PpG3TldtKrC6aI\n"
        "Z2m2XJdY8dMHVKBiby0tZGgqfA==\n"
        "-----END CERTIFICATE-----\n";

    boost::system::error_code ec;
    // adds the certificate to the SSL context list of trusted certificates using ctx.add_certificate_authority
    ctx.add_certificate_authority(
        boost::asio::buffer(cert.data(), cert.size()), ec);

    // if any error then throw
    if (ec)
        throw boost::system::system_error{ec};
}


#endif // ROOT_CERTIFICATES_HPP
