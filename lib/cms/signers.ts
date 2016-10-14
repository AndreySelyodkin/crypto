import * as native from "../native";
import * as object from "../object";
import * as Collection from "../core/collection";
import {Signer} from "./signer";


/**
 * Collection of Signer
 *
 * @export
 * @class SignerCollection
 * @extends {object.BaseObject<native.CMS.SignerCollection>}
 * @implements {Collection.ICollection}
 */
export class SignerCollection extends object.BaseObject<native.CMS.SignerCollection> implements Collection.ICollection {

    /**
     * Creates an instance of SignerCollection.
     *
     * @param {native.CMS.SignerCollection} nativeHandle
     *
     * @memberOf SignerCollection
     */
    constructor(nativeHandle: native.CMS.SignerCollection) {
        super();

        this.handle = nativeHandle;
    }

    /**
     * Return element by index from collection
     *
     * @param {number} index
     * @returns {Signer}
     *
     * @memberOf SignerCollection
     */
    public items(index: number): Signer {
        return new Signer(this.handle.items(index));
    }

    /**
     * Return collection length
     *
     * @readonly
     * @type {number}
     * @memberOf SignerCollection
     */
    get length(): number {
        return this.handle.length();
    }

}
