#include "../stdafx.h"

#include "wcert.h"
#include "wkey.h"

const char* WCertificate::className = "Certificate";

void WCertificate::Init(v8::Handle<v8::Object> exports) {
	METHOD_BEGIN();

	v8::Local<v8::String> className = Nan::New(WCertificate::className).ToLocalChecked();

	// Basic instance setup
	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);

	tpl->SetClassName(className);
	tpl->InstanceTemplate()->SetInternalFieldCount(1); // req'd by ObjectWrap

	Nan::SetPrototypeMethod(tpl, "getSubjectFriendlyName", GetSubjectFriendlyName);
	Nan::SetPrototypeMethod(tpl, "getIssuerFriendlyName", GetIssuerFriendlyName);
	Nan::SetPrototypeMethod(tpl, "getSubjectName", GetSubjectName);
	Nan::SetPrototypeMethod(tpl, "getIssuerName", GetIssuerName);
	Nan::SetPrototypeMethod(tpl, "getNotAfter", GetNotAfter);
	Nan::SetPrototypeMethod(tpl, "getNotBefore", GetNotBefore);
	Nan::SetPrototypeMethod(tpl, "getSerialNumber", GetSerialNumber);
	Nan::SetPrototypeMethod(tpl, "getThumbprint", GetThumbprint);
	Nan::SetPrototypeMethod(tpl, "getVersion", GetVersion);
	Nan::SetPrototypeMethod(tpl, "getType", GetType);
	Nan::SetPrototypeMethod(tpl, "getKeyUsage", GetKeyUsage);
	Nan::SetPrototypeMethod(tpl, "getSignatureAlgorithm", GetSignatureAlgorithm);
	Nan::SetPrototypeMethod(tpl, "getSignatureDigest", GetSignatureDigest);
	Nan::SetPrototypeMethod(tpl, "getOrganizationName", GetOrganizationName);

	Nan::SetPrototypeMethod(tpl, "load", Load);
	Nan::SetPrototypeMethod(tpl, "import", Import);
	Nan::SetPrototypeMethod(tpl, "save", Save);
	Nan::SetPrototypeMethod(tpl, "export", Export);
	Nan::SetPrototypeMethod(tpl, "compare", Compare);
	Nan::SetPrototypeMethod(tpl, "equals", Equals);
	Nan::SetPrototypeMethod(tpl, "duplicate", Duplicate);
	Nan::SetPrototypeMethod(tpl, "hash", Hash);

	// Store the constructor in the target bindings.
	constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());

	exports->Set(Nan::New(WCertificate::className).ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(WCertificate::New) {
	METHOD_BEGIN();

	try {
		WCertificate *obj = new WCertificate();
		obj->data_ = new Certificate();

		obj->Wrap(info.This());

		info.GetReturnValue().Set(info.This());
		return;
	}
	TRY_END();
}

/*
 * filename: String
 * format: DataFormat
 */
NAN_METHOD(WCertificate::Load) {
	METHOD_BEGIN();

	try {
		LOGGER_ARG("filename");
		v8::String::Utf8Value v8Filename(info[0]->ToString());
		char *filename = *v8Filename;

		LOGGER_ARG("format");
		int format = info[1]->ToNumber()->Int32Value();

		UNWRAP_DATA(Certificate);

		Handle<Bio> in = NULL;

		in = new Bio(BIO_TYPE_FILE, filename, "rb");

		_this->read(in, DataFormat::get(format));

		info.GetReturnValue().Set(info.This());
		return;
	}
	TRY_END();
}

/*
 * data: Buffer
 * format: DataFormat
 */
NAN_METHOD(WCertificate::Import) {
	METHOD_BEGIN();

	try {
		LOGGER_ARG("data");
		char* buf = node::Buffer::Data(info[0]->ToObject());
		size_t buflen = node::Buffer::Length(info[0]);
		std::string buffer(buf, buflen);

		LOGGER_ARG("format");
		int format = info[1]->ToNumber()->Int32Value();

		UNWRAP_DATA(Certificate);

		Handle<Bio> in = new Bio(BIO_TYPE_MEM, buffer);

		_this->read(in, DataFormat::get(format));

		info.GetReturnValue().Set(info.This());
		return;
	}
	TRY_END();
}

/*
* filename: String
* format: DataFormat
*/
NAN_METHOD(WCertificate::Save) {
	METHOD_BEGIN();

	try {
		LOGGER_ARG("filename");
		v8::String::Utf8Value v8Filename(info[0]->ToString());
		char *filename = *v8Filename;

		LOGGER_ARG("format");
		int format = info[1]->ToNumber()->Int32Value();

		UNWRAP_DATA(Certificate);

		Handle<Bio> out = new Bio(BIO_TYPE_FILE, filename, "wb");
		_this->write(out, DataFormat::get(format));
		out->flush();

		info.GetReturnValue().Set(info.This());
		return;
	}
	TRY_END();
}

/*
 * format: DataFormat
 */
NAN_METHOD(WCertificate::Export) {
	METHOD_BEGIN();

	try {
		LOGGER_ARG("format")
		int format = info[0]->ToNumber()->Int32Value();

		UNWRAP_DATA(Certificate);

		Handle<Bio> out = new Bio(BIO_TYPE_MEM, "");
		_this->write(out, DataFormat::get(format));

		Handle<std::string> buf = out->read();

		info.GetReturnValue().Set(
			stringToBuffer(buf)
			);
		return;
	}
	TRY_END();
}

NAN_METHOD(WCertificate::GetSubjectFriendlyName) {
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		Handle<std::string> fname = _this->getSubjectFriendlyName();

		v8::Local<v8::String> v8FName = Nan::New<v8::String>(fname->c_str()).ToLocalChecked();

		info.GetReturnValue().Set(v8FName);
		return;
	}
	TRY_END();
}

NAN_METHOD(WCertificate::GetIssuerFriendlyName) {
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		Handle<std::string> fname = _this->getIssuerFriendlyName();

		v8::Local<v8::String> v8FName = Nan::New<v8::String>(fname->c_str()).ToLocalChecked();

		info.GetReturnValue().Set(v8FName);
		return;
	}
	TRY_END();
}

NAN_METHOD(WCertificate::GetSubjectName) {
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		Handle<std::string> name = _this->getSubjectName();

		v8::Local<v8::String> v8Name = Nan::New<v8::String>(name->c_str()).ToLocalChecked();

		info.GetReturnValue().Set(v8Name);
		return;
	}
	TRY_END();
}

NAN_METHOD(WCertificate::GetIssuerName) {
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		Handle<std::string> name = _this->getIssuerName();

		v8::Local<v8::String> v8Name = Nan::New<v8::String>(name->c_str()).ToLocalChecked();

		info.GetReturnValue().Set(v8Name);
		return;
	}
	TRY_END();
}

NAN_METHOD(WCertificate::GetNotBefore)
{
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		Handle<std::string> time = _this->getNotBefore();

		v8::Local<v8::String> v8Time = Nan::New<v8::String>(time->c_str()).ToLocalChecked();

		info.GetReturnValue().Set(v8Time);
		return;
	}
	TRY_END();
}

NAN_METHOD(WCertificate::GetNotAfter)
{
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		Handle<std::string> time = _this->getNotAfter();

		v8::Local<v8::String> v8Time = Nan::New<v8::String>(time->c_str()).ToLocalChecked();

		info.GetReturnValue().Set(v8Time);
		return;
	}
	TRY_END();
}

NAN_METHOD(WCertificate::GetSerialNumber)
{
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		Handle<std::string> buf = _this->getSerialNumber();

		info.GetReturnValue().Set(
			stringToBuffer(buf)
			);
		return;
	}
	TRY_END();
}

NAN_METHOD(WCertificate::GetThumbprint)
{
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		Handle<std::string> buf = _this->getThumbprint();

		info.GetReturnValue().Set(
			stringToBuffer(buf)
			);

		return;
	}
	TRY_END();
}

/*
* certificate: Certificate
*/
NAN_METHOD(WCertificate::Compare) {
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		LOGGER_ARG("certificate")
		WCertificate* obj = (WCertificate*)Nan::GetInternalFieldPointer(info[0]->ToObject(), 0);
		Handle<Certificate> cert = obj->data_;

		int res = _this->compare(cert);

		v8::Local<v8::Number> v8Number = Nan::New<v8::Number>(res);

		info.GetReturnValue().Set(v8Number);
		return;
	}
	TRY_END();
}

/*
 * certificate: Certificate
 */
NAN_METHOD(WCertificate::Equals) {
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		LOGGER_ARG("certificate")
		WCertificate* obj = (WCertificate*)Nan::GetInternalFieldPointer(info[0]->ToObject(), 0);
		Handle<Certificate> cert = obj->data_;

		bool res = _this->equals(cert);

		info.GetReturnValue().Set(
			Nan::New<v8::Boolean>(res)
			);
		return;
	}
	TRY_END();
}

NAN_METHOD(WCertificate::GetVersion)
{
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		long version = _this->getVersion();

		info.GetReturnValue().Set(
			Nan::New<v8::Number>(version)
			);
		return;
	}
	TRY_END();
}

NAN_METHOD(WCertificate::GetType)
{
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		int type = _this->getType();

		info.GetReturnValue().Set(
			Nan::New<v8::Number>(type)
			);
		return;
	}
	TRY_END();
}

NAN_METHOD(WCertificate::GetKeyUsage)
{
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		int type = _this->getKeyUsage();

		info.GetReturnValue().Set(Nan::New<v8::Number>(type));
		return;
	}
	TRY_END();
}

NAN_METHOD(WCertificate::GetSignatureAlgorithm)
{
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		Handle<std::string> sigAlg = _this->getSignatureAlgorithm();

		v8::Local<v8::String> v8SigAlg = Nan::New<v8::String>(sigAlg->c_str()).ToLocalChecked();

		info.GetReturnValue().Set(v8SigAlg);
		return;
	}
	TRY_END();
}

NAN_METHOD(WCertificate::GetSignatureDigest)
{
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		Handle<std::string> sigAlg = _this->getSignatureDigest();

		v8::Local<v8::String> v8SigAlg = Nan::New<v8::String>(sigAlg->c_str()).ToLocalChecked();

		info.GetReturnValue().Set(v8SigAlg);
		return;
	}
	TRY_END();
}

NAN_METHOD(WCertificate::GetOrganizationName)
{
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		Handle<std::string> orgName = _this->getOrganizationName();

		v8::Local<v8::String> v8OrgName = Nan::New<v8::String>(orgName->c_str()).ToLocalChecked();

		info.GetReturnValue().Set(v8OrgName);
		return;
	}
	TRY_END();
}

NAN_METHOD(WCertificate::Duplicate)
{
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		Handle<Certificate> cert = _this->duplicate();

		LOGGER_INFO("Create new instance of JS Certificate");
		v8::Local<v8::Object> v8CertificateClass = Nan::New<v8::Object>();
		WCertificate::Init(v8CertificateClass);
		v8::Local<v8::Object> v8Certificate = Nan::Get(v8CertificateClass, Nan::New("Certificate").ToLocalChecked()).ToLocalChecked()->ToObject()->CallAsConstructor(0, NULL)->ToObject();

		LOGGER_INFO("Set internal data for JS Certificate");
		WCertificate* wcert = (WCertificate*)Nan::GetInternalFieldPointer(v8Certificate, 0);
		wcert->data_ = cert;

		info.GetReturnValue().Set(v8Certificate);
		return;
	}
	TRY_END();
}

/*
 * algorithm: String
 */
NAN_METHOD(WCertificate::Hash)
{
	METHOD_BEGIN();

	try {
		UNWRAP_DATA(Certificate);

		LOGGER_ARG("algorithm")
		v8::String::Utf8Value v8Alg(info[0]->ToString());
		char *alg = *v8Alg;

		Handle<std::string> hash = _this->hash(new std::string(alg));
		
		info.GetReturnValue().Set(stringToBuffer(hash));
		return;
	}
	TRY_END();
}