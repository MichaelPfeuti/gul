#pragma once
#ifndef _GUL_PERSISTANCE_XML_SAVER_H_
#define _GUL_PERSISTANCE_XML_SAVER_H_

/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011 Michael Pfeuti.
**
** Contact: Michael Pfeuti (mpfeuti@ganymede.ch)
**
**
** gul is free software: you can redistribute it and/or modify it under the
** terms of the GNU Lesser General Public License as published by the Free
** Software Foundation, either version 3 of the License, or (at your option)
** any later version.
**
** gul is distributed in the hope that it will be useful, but WITHOUT ANY
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
** more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with gul. If not, see <http://www.gnu.org/licenses/>.
**
**
** If you have questions regarding the use of this file, please contact
** Michael Pfeuti at mpfeuti@ganymede.ch.
**
***************************************************************************/

#include <typeinfo>

#include <3rdParty/pugi/pugixml.hpp>
#include "Map.h"
#include "String.h"

namespace gul
{

/** this enforces that saved is initially false */
class XMLSerializer
{
protected:
    XMLSerializer() : __saved (false) {}
    bool __saved;
};

}



typedef gul::Map<gul::String, void*> InstanceMap;

#define DECLARE_SERIALIZABLE() \
    private: \
        static InstanceMap __loadedInstances; \
        virtual void ResetSaveStatus() { Save(true); } \
        virtual void ResetLoadStatusFor(pugi::xml_node node) { Load(node, true); } \
    public:\
        virtual void Save(pugi::xml_node& node, bool resetMode = false); \
        virtual void* Load(const pugi::xml_node& node, bool resetMode = false); \
    private:



#define DECLARE_SERIALIZABLE_BASE_CLASS() \
    private: \
        static InstanceMap __loadedInstances; \
        virtual void ResetSaveStatus() { Save(true); } \
        virtual void ResetLoadStatusFor(pugi::xml_node node) { Load(node, true); } \
    public:\
        virtual pugi::xml_node Save(pugi::xml_node& node, bool resetMode = false); \
        virtual void* Load(const pugi::xml_node& node, bool resetMode = false) ; \
        virtual pugi::xml_node Save(pugi::xml_node node, bool resetMode = false); \
        virtual void* Load(const pugi::xml_node& node, void* instanceVoid, bool resetMode = false); \
    private:


#define DECLARE_SERIALIZABLE_ABSTRACT_CLASS() \
    private: \
        virtual void ResetSaveStatus() { Save(true); } \
        virtual void ResetLoadStatusFor(pugi::xml_node node) { Load(node, true); } \
        friend class XMLGameSaver; \
        friend class XMLGameLoader; \
    public:\
        virtual pugi::xml_node Save(bool resetMode = false) = 0; \
        virtual void* Load(const pugi::xml_node& node, bool resetMode = false) = 0; \
        virtual pugi::xml_node Save(pugi::xml_node node, bool resetMode = false); \
        virtual void* Load(const pugi::xml_node& node, void* instanceVoid, bool resetMode = false); \
    private:




// SAVING MACROS
#define BEGIN_SAVE(className) \
        pugi::xml_node className::Save(bool resetMode) { \
            if(resetMode && !__saved)  { /*in this case this node was already reset*/ \
                resetMode = false; \
                pugi::xml_node resetNode; \
                resetNode.set_name(#className); \
                return resetNode;  \
            }  \
            if(resetMode) \
                __saved = false; \
            int i; unsigned int ui; \
            short s; unsigned short us; \
            long l; unsigned long ul; \
            float f; \
            double d;\
            bool b; \
            pugi::xml_node listNode; \
            pugi::xml_node node; \
            node.set_name(#className); \
            pugi::xml_node childNode; \
            UNUSED_VARIABLE(i); \
            UNUSED_VARIABLE(ui); \
            UNUSED_VARIABLE(s); \
            UNUSED_VARIABLE(us); \
            UNUSED_VARIABLE(l); \
            UNUSED_VARIABLE(ul); \
            UNUSED_VARIABLE(f); \
            UNUSED_VARIABLE(d); \
            UNUSED_VARIABLE(b); \
            UNUSED_VARIABLE(listNode); \
            UNUSED_VARIABLE(childNode); \
            if (__saved && !resetMode) { \
                node.append_attribute("__ref").set_value(__index); \
                return node; \
            } \
            __index = __maxIndex++; \
            SAVE_PRIMITIVE(__index); \
            if(!resetMode)  \
                __saved = true;


#define BEGIN_SAVE_BASE_CLASS(className) \
        pugi::xml_node className::Save(pugi::xml_node node, bool resetMode) { \
            int i; unsigned int ui; \
            short s; unsigned short us; \
            long l; unsigned long ul; \
            float f; \
            double d;\
            bool b; \
            pugi::xml_node listNode; \
            pugi::xml_node childNode; \
            UNUSED_VARIABLE(i); \
            UNUSED_VARIABLE(ui); \
            UNUSED_VARIABLE(s); \
            UNUSED_VARIABLE(us); \
            UNUSED_VARIABLE(l); \
            UNUSED_VARIABLE(ul); \
            UNUSED_VARIABLE(f); \
            UNUSED_VARIABLE(d); \
            UNUSED_VARIABLE(b); \
            UNUSED_VARIABLE(listNode); \
            UNUSED_VARIABLE(childNode);


#define SAVE_BASE_CLASS(className) \
            className::Save(node, resetMode);


#define SAVE_STRING(attributeArg) \
    if(!resetMode) \
    { \
        node.append_attribute(#attributeArg).set_value(attributeArg); \
    }


#define SAVE_PRIMITIVE(attributeArg) \
    if(!resetMode) \
    { \
        node.append_attribute(#attributeArg).set_value(attributeArg); \
    }


#define SAVE_POINTER(attributeArg) \
    if(attributeArg != NULL) \
    { \
        childNode = attributeArg->Save(resetMode); \
        childNode.append_attribute("attributeName").set_value(#attributeArg); \
        if(!resetMode) \
            node.append_copy(childNode); \
    }


#define SAVE_VARIABLE(attributeArg) \
    childNode = attributeArg.Save(resetMode); \
    childNode.append_attribute("attributeName").set_value(#attributeArg); \
    if(!resetMode) \
        node.append_copy(childNode);


#define END_SAVE_BASE_CLASS(className) \
    return node;\
}


#define END_SAVE(className) \
    return node;\
}






// LOADING MACROS
#define BEGIN_LOAD(className) \
    \
    REGISTER_CLASS_FACTORY(className) \
    \
    InstanceMap className::__loadedInstances =  InstanceMap(); \
            \
    void* className::Load(const pugi::xml_node& node, bool resetMode) { \
        if(resetMode) \
            className::__loadedInstances.clear(); \
        int i; unsigned int ui; \
        short s; unsigned short us; \
        long l; unsigned long ul; \
        float f; \
        double d;\
        bool b; \
        wxString string; \
        pugi::xml_node listNode; \
        wxString attrString; \
        UNUSED_VARIABLE(i); \
        UNUSED_VARIABLE(ui); \
        UNUSED_VARIABLE(s); \
        UNUSED_VARIABLE(us); \
        UNUSED_VARIABLE(l); \
        UNUSED_VARIABLE(ul); \
        UNUSED_VARIABLE(f); \
        UNUSED_VARIABLE(d); \
        UNUSED_VARIABLE(b); \
        UNUSED_VARIABLE(listNode); \
        if (!resetMode && !node.attribute("__ref").empty()) { \
            string = wxString(node.attribute("__ref").value(), wxConvUTF8); \
            void* ptr = className::__loadedInstances.find(string)->second; \
            return ptr; \
        } \
        className* instance; \
        if(!resetMode) \
            instance = new className(); \
        LOAD_PRIMITIVE(__index); \
        if(!resetMode) { \
            wxString iString; iString.Printf(_T("%d"), instance->__index); \
            InstanceMap::value_type val(iString, instance); \
            className::__loadedInstances.insert(val); \
        }


#define BEGIN_LOAD_BASE_ClASS(className) \
    void* className::Load(const pugi::xml_node& node, void* instanceVoid, bool resetMode) { \
        int i; unsigned int ui; \
        short s; unsigned short us; \
        long l; unsigned long ul; \
        float f; \
        double d;\
        bool b; \
        wxString string; \
        pugi::xml_node listNode; \
        wxString attrString; \
        UNUSED_VARIABLE(i); \
        UNUSED_VARIABLE(ui); \
        UNUSED_VARIABLE(s); \
        UNUSED_VARIABLE(us); \
        UNUSED_VARIABLE(l); \
        UNUSED_VARIABLE(ul); \
        UNUSED_VARIABLE(f); \
        UNUSED_VARIABLE(d); \
        UNUSED_VARIABLE(b); \
        UNUSED_VARIABLE(listNode); \
        className* instance; \
        if(!resetMode) \
            instance = (className*) instanceVoid;


#define LOAD_BASE_CLASS(className) \
        className::Load(node, instance, resetMode);


#define LOAD_STRING(attributeArg) \
    if (!resetMode && !node.attribute(#attributeArg).empty()) { \
        string = wxString(node.attribute(#attributeArg).value(), wxConvUTF8); \
        instance->attributeArg = string; \
    } \


// TODO: check signed/unsigned
#define LOAD_PRIMITIVE(attributeArg) \
    if (!resetMode && !node.attribute(#attributeArg).empty()) { \
        attrString = wxString(node.attribute(#attributeArg).value(), wxConvUTF8); \
        if (typeid(attributeArg) == typeid(i) || typeid(attributeArg) == typeid(s) || \
            typeid(attributeArg) == typeid(l) || typeid(attributeArg) == typeid(ui) || \
            typeid(attributeArg) == typeid(us) || typeid(attributeArg) == typeid(ul)) { \
            long value; \
            attrString.ToLong(&value); \
            instance->attributeArg = value; \
        } else if (typeid(attributeArg) == typeid(d) || typeid(attributeArg) == typeid(f)) { \
            double value; \
            attrString.ToDouble(&value); \
            instance->attributeArg = value; \
        } else if (typeid(attributeArg) == typeid(b)) { \
            instance->attributeArg = _T("true") == attrString; \
        } else { \
            FAIL("Invalid Primitive!"); \
        }\
    }


#define LOAD_POINTER(attributeArg, className) \
    listNode = node.first_child(); \
    while (!listNode.empty()) { \
        string = wxString(listNode.attribute("attributeName").value(),wxConvUTF8); \
        if (string==wxT(#attributeArg)) { \
            className* loaderObject = (className*) ClassFactory::CreateInstance(wxString(listNode.name(), wxConvUTF8));   \
            className* myObject = (className*) loaderObject->Load(listNode, resetMode); \
            delete loaderObject; \
            if(!resetMode) { \
                instance->attributeArg = myObject; \
            } \
        } \
        listNode = listNode.next_sibling();  \
    }


#define LOAD_VARIABLE(attributeArg, className) \
    listNode = node.first_child(); \
    while (!listNode.empty()) { \
       string = wxString(listNode.attribute("attributeName").value(), wxConvUTF8); \
       if (wxString(listNode.name(), wxConvUTF8).Cmp(wxT(#className)) == 0 && string==wxT(#attributeArg)) { \
            className loaderObject; \
            className* heapData = (className*) loaderObject.Load(listNode, resetMode); \
            if(!resetMode) { \
                instance->attributeArg = *heapData; \
                delete heapData; \
            } \
        } \
        listNode = listNode.next_sibling();  \
    }


#define END_LOAD_BASE_CLASS(className) \
        return instance; \
    }


#define END_LOAD(className) \
        return instance; \
    }


#endif // XMLGAMEMACROS_H
