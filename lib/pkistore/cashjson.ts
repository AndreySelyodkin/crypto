/// <reference path="../native.ts" />
/// <reference path="../object.ts" />

namespace trusted.pkistore {
    /**
     * Work with json files
     *
     * @export
     * @class CashJson
     * @extends {BaseObject<native.PKISTORE.CashJson>}
     */
    export class CashJson extends BaseObject<native.PKISTORE.CashJson> {
        /**
         * Creates an instance of CashJson.
         *
         * @param {string} fileName File path
         *
         * @memberOf CashJson
         */
        constructor(fileName: string) {
            super();
            this.handle = new native.PKISTORE.CashJson(fileName);
        }

        /**
         * Return PkiItems from json
         *
         * @returns {native.PKISTORE.IPkiItem[]}
         *
         * @memberOf CashJson
         */
        public export(): native.PKISTORE.IPkiItem[] {
            return this.handle.export();
        }

        /**
         * Import PkiItems to json
         *
         * @param {native.PKISTORE.IPkiItem[]} items
         *
         * @memberOf CashJson
         */
        public import(items: native.PKISTORE.IPkiItem[]): void {
            for (let i: number = 0; i < items.length; i++) {
                let pkiItem: PkiItem = new PkiItem();

                pkiItem.format = items[i].format;
                pkiItem.type = items[i].type;
                pkiItem.category = items[i].category;
                pkiItem.provider = items[i].provider;
                pkiItem.uri = items[i].uri;
                pkiItem.hash = items[i].hash.toLocaleLowerCase();
                if (items[i].subjectName) {
                    pkiItem.subjectName = items[i].subjectName;
                }
                if (items[i].subjectFriendlyName) {
                    pkiItem.subjectFriendlyName = items[i].subjectFriendlyName;
                }
                if (items[i].issuerName) {
                    pkiItem.issuerName = items[i].issuerName;
                }
                if (items[i].issuerFriendlyName) {
                    pkiItem.issuerFriendlyName = items[i].issuerFriendlyName;
                }
                if (items[i].serial) {
                    pkiItem.serial = items[i].serial;
                }
                if (items[i].notBefore) {
                    pkiItem.notBefore = items[i].notBefore;
                }
                if (items[i].notAfter) {
                    pkiItem.notAfter = items[i].notAfter;
                }
                if (items[i].lastUpdate) {
                    pkiItem.lastUpdate = items[i].lastUpdate;
                }
                if (items[i].nextUpdate) {
                    pkiItem.nextUpdate = items[i].nextUpdate;
                }
                if (items[i].key) {
                    pkiItem.key = items[i].key;
                }
                if (items[i].encrypted) {
                    pkiItem.keyEnc = items[i].encrypted;
                }
                if (items[i].organizationName) {
                    pkiItem.organizationName = items[i].organizationName;
                }
                if (items[i].signatureAlgorithm) {
                    pkiItem.signatureAlgorithm = items[i].signatureAlgorithm;
                }

                this.handle.import(pkiItem.handle);
            }
        }
    }
}
