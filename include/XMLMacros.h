#ifndef XMLGAMEMACROS_H
#define XMLGAMEMACROS_H

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

#include <xml/XMLGameLoader.h>
#include <xml/XMLGameSaver.h>

/** this enforces that saved is initially false */
class XMLSerializer
{
protected:
    XMLSerializer() : __saved (false) {}
    bool __saved;
};

WX_DECLARE_STRING_HASH_MAP( void*, InstanceMap);

#define DECLARE_SERIALIZABLE() \
    private: \
        static InstanceMap __loadedInstances; \
        virtual void ResetSaveStatus() { Save(true); } \
        virtual void ResetLoadStatusFor(pugi::xml_node node) { Load(node, true); } \
        friend class XMLGameSaver; \
        friend class XMLGameLoader; \
    public:\
        virtual void Save(pugi::xml_node& node, bool resetMode = false); \
        virtual void* Load(const pugi::xml_node& node, bool resetMode = false);



#define DECLARE_SERIALIZABLE_BASE_CLASS() \
    private: \
        static InstanceMap __loadedInstances; \
        virtual void ResetSaveStatus() { Save(true); } \
        virtual void ResetLoadStatusFor(pugi::xml_node node) { Load(node, true); } \
        friend class XMLGameSaver; \
        friend class XMLGameLoader; \
    public:\
        virtual pugi::xml_node Save(pugi::xml_node& node, bool resetMode = false); \
        virtual void* Load(const pugi::xml_node& node, bool resetMode = false) ; \
        virtual pugi::xml_node Save(pugi::xml_node node, bool resetMode = false); \
        virtual void* Load(const pugi::xml_node& node, void* instanceVoid, bool resetMode = false);


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
        virtual void* Load(const pugi::xml_node& node, void* instanceVoid, bool resetMode = false);




// SAVING MACROS
#define BEGIN_SAVE(index, className) \
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
                node.append_attribute("__ref").set_value((int)index); \
                return node; \
            } \
            SAVE_PRIMITIVE((int)index); \
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
        node.append_attribute(#attributeArg).set_value(attributeArg);


#define SAVE_PRIMITIVE(attributeArg) \
    if(!resetMode) \
    { \
        node.append_attribute(#attributeArg).set_value(attributeArg); \
    }


#define SAVE_POINTER(attributeArg) \
    if(attributeArg != NULL) { \
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


#define SAVE_VALUE_ARRAY(attributeArg) \
    if(!resetMode) \
    { \
        listNode = pugi::xml_node(); \
        listNode.set_name(#attributeArg); \
        for (int i = 0; i < attributeArg.GetCount(); i++) { \
            pugi::xml_node itemNode = attributeArg.Item(i).Save(); \
            listNode.append_copy(itemNode); \
        } \
        node.append_copy(listNode); \
    } else { \
        for (unsigned int i = 0; i < attributeArg.GetCount(); i++)  \
            attributeArg.Item(i).Save(true); \
    }


#define SAVE_ARRAYSTRING(attributeArg) \
    if(!resetMode) \
    { \
        listNode = pugi::xml_node(); \
        listNode.set_name(#attributeArg); \
        for (unsigned int i = 0; i < attributeArg.GetCount(); i++) { \
            wxString iString; iString.Printf(_T("item%d"), i); \
            pugi::xml_node itemNode = pugi::xml_node(); \
            itemNode.set_name(iString.mb_str()); \
            itemNode.append_attribute("value").set_value(attributeArg.Item(i).mb_str()); \
            listNode.append_copy(itemNode); \
        } \
        node.append_copy(listNode); \
    }


#define SAVE_ARRAY(attributeArg) \
    if(attributeArg != NULL) { \
        if(!resetMode) \
        { \
            listNode = pugi::xml_node(); \
            listNode.set_name(#attributeArg); \
            for (int i = 0; i < attributeArg->GetCount(); i++) { \
                pugi::xml_node itemNode = attributeArg->Item(i)->Save(); \
                listNode.append_copy(itemNode); \
            } \
            node.append_copy(listNode); \
        } else { \
            for (int i = 0; i < attributeArg->GetCount(); i++)  \
                attributeArg->Item(i)->Save(true); \
        }\
    }

#define SAVE_VALUE_LIST(attributeArg) \
    if(attributeArg != NULL) { \
        if(!resetMode) \
        { \
            listNode = pugi::xml_node(); \
            listNode.set_name(#attributeArg); \
            for (int i = 0; i < attributeArg->Size(); i++) { \
                pugi::xml_node itemNode = attributeArg->Get(i).Save(); \
                listNode.append_copy(itemNode); \
            } \
            node.append_copy(listNode); \
        } else { \
            for (int i = 0; i < attributeArg->Size(); i++)  \
                attributeArg.Get(i).Save(true); \
        } \
    }


#define SAVE_LIST(attributeArg) \
    if(attributeArg != NULL) { \
        if(!resetMode) \
        { \
            listNode = pugi::xml_node(); \
            listNode.set_name(#attributeArg); \
            for (int i = 0; i < attributeArg->GetCount(); i++) { \
                pugi::xml_node itemNode = attributeArg->Item(i)->GetData()->Save(); \
                listNode.append_copy(itemNode); \
            } \
            node.append_copy(listNode); \
        } else { \
            for (int i = 0; i < attributeArg->GetCount(); i++)  \
                attributeArg->Item(i)->GetData()->Save(true); \
        } \
    }


#define SAVE_ARRAY_ARRAY(attributeArg) \
    if(attributeArg != NULL) { \
        if(!resetMode) \
        { \
            listNode = pugi::xml_node(); \
            listNode.set_name(#attributeArg); \
            for (int i = 0; i < attributeArg->GetCount(); i++) { \
                wxString iString; iString.Printf(_T("sublist%u"), i); \
                pugi::xml_node sublistNode = pugi::xml_node(); \
                sublistNode.set_name(iString.mb_str()); \
                for (int j = 0; j < attributeArg->Item(i)->GetCount(); j++) { \
                    pugi::xml_node itemNode = attributeArg->Item(i)->Item(j)->Save(); \
                    sublistNode.append_copy(itemNode); \
                } \
                listNode.append_copy(sublistNode); \
            } \
            node.append_copy(listNode); \
        } else { \
            for (int i = 0; i < attributeArg->GetCount(); i++) { \
            for (int j = 0; j < attributeArg->Item(i)->GetCount(); j++){  \
                attributeArg->Item(i)->Item(j)->Save(true); \
            }}\
        } \
    }


#define SAVE_HASHMAP(attributeArg, hashClassName) \
    if(attributeArg != NULL) { \
        hashClassName::iterator it = attributeArg->begin(); \
        if(!resetMode) \
        { \
            listNode = pugi::xml_node(); \
            listNode.set_name(#attributeArg); \
            while(it != attributeArg->end()) { \
                pugi::xml_node itemNode = it->first->Save(); \
                listNode.append_copy(itemNode); \
                itemNode = it->second->Save(); \
                listNode.append_copy(itemNode); \
                it++; \
            } \
            node.append_copy(listNode); \
        } else { \
            while(it != attributeArg->end()) { \
                it->second->Save(true); \
                it++; \
            }\
        } \
    }


#define END_SAVE_BASE_CLASS(className) \
    return node;\
}


#define END_SAVE(index, className) \
    return node;\
}






// LOADING MACROS
#define BEGIN_LOAD(index, className) \
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
        LOAD_PRIMITIVE(index); \
        if(!resetMode) { \
            wxString iString; iString.Printf(_T("%d"), instance->index); \
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
            wxFAIL_MSG("Invalid Primitive!"); \
        }\
    } \


#define LOAD_ARRAYSTRING(attributeArg) \
    listNode = node.first_child(); \
    while (!resetMode && !listNode.empty()) { \
        if (wxString(listNode.name(), wxConvUTF8).Cmp(wxT(#attributeArg)) == 0) { \
            pugi::xml_node itemNode = listNode.first_child(); \
            while(!itemNode.empty()) { \
                string = wxString(itemNode.attribute("value").value(), wxConvUTF8); \
                instance->attributeArg.Add(string); \
                itemNode = itemNode.next_sibling(); \
            } \
        } else { \
        }\
        listNode = listNode.next_sibling();  \
    }


#define LOAD_VALUE_ARRAY(attributeArg, className) \
    listNode = node.first_child(); \
    while (!listNode.empty()) { \
        if (wxString(listNode.name(), wxConvUTF8).Cmp(wxT(#attributeArg)) == 0) { \
            pugi::xml_node itemNode = listNode.first_child(); \
            while(!itemNode.empty()) { \
                className loaderObject; \
                className* myObject = (className*) loaderObject.Load(itemNode, resetMode); \
                if(!resetMode) { \
                    instance->attributeArg.Add(*myObject); \
                    delete myObject; \
                } \
                itemNode = itemNode.next_sibling(); \
            } \
        } else { \
        }\
        listNode = listNode.next_sibling();  \
    }


#define LOAD_ARRAY(attributeArg, className) \
    listNode = node.first_child(); \
    while (!listNode.empty()) { \
        if (wxString(listNode.name(), wxConvUTF8).Cmp(wxT(#attributeArg)) == 0) { \
            pugi::xml_node itemNode = listNode.first_child(); \
            while(!itemNode.empty()) { \
                className* loaderObject = (className*) ClassFactory::CreateInstance(wxString(itemNode.name(), wxConvUTF8));   \
                className* myObject = (className*) loaderObject->Load(itemNode, resetMode); \
                delete loaderObject; \
                if(!resetMode) { \
                    instance->attributeArg->Add(myObject); \
                } \
                itemNode = itemNode.next_sibling(); \
            } \
        } else { \
        }\
        listNode = listNode.next_sibling();  \
    }


#define LOAD_LIST(attributeArg, className) \
    listNode = node.first_child(); \
    while (!listNode.empty()) { \
        if (wxString(listNode.name(), wxConvUTF8).Cmp(wxT(#attributeArg)) == 0) { \
            pugi::xml_node itemNode = listNode.first_child(); \
            while(!itemNode.empty()) { \
                className loaderObject; \
                className* myObject = (className*) loaderObject.Load(itemNode, resetMode); \
                if(!resetMode) { \
                    instance->attributeArg->Append(myObject); \
                } \
                itemNode = itemNode.next_sibling(); \
            } \
        } else { \
        } \
        listNode = listNode.next_sibling();  \
    }


#define LOAD_ARRAY_ARRAY(attributeArg, className, containerName) \
    listNode = node.first_child(); \
    while (!listNode.empty()) { \
        if (wxString(listNode.name(), wxConvUTF8).Cmp(wxT(#attributeArg)) == 0) { \
            pugi::xml_node sublistNode = listNode.first_child(); \
            while(!sublistNode.empty()) { \
                pugi::xml_node itemNode = sublistNode.first_child(); \
                containerName* container = new containerName(); \
                while(!itemNode.empty()) { \
                  className* loaderObject = (className*) ClassFactory::CreateInstance(wxString(itemNode.name(), wxConvUTF8));   \
                  className* myObject = (className*) loaderObject->Load(itemNode, resetMode); \
                  delete loaderObject; \
                  if(!resetMode) { \
                    container->Add(myObject); \
                  } \
                  itemNode = itemNode.next_sibling(); \
                } \
                if(!resetMode) { \
                    instance->attributeArg->Add(container); \
                } else { \
                    delete container; \
                } \
                sublistNode = sublistNode.next_sibling(); \
            } \
        } else { \
        }\
        listNode = listNode.next_sibling();  \
    }


#define LOAD_HASHMAP(attributeArg, hashClassName, keyClassName, valueClassName) \
    listNode = node.first_child(); \
    while (!listNode.empty()) { \
        if (wxString(listNode.name(), wxConvUTF8).Cmp(wxT(#attributeArg)) == 0) { \
            pugi::xml_node itemNode = listNode.first_child(); \
            while(!itemNode.empty()) { \
              keyClassName* firstloaderObject = (keyClassName*) ClassFactory::CreateInstance(wxString(itemNode.name(),wxConvUTF8));   \
              keyClassName* firstObject = (keyClassName*) firstloaderObject->Load(itemNode, resetMode); \
              delete firstloaderObject; \
              itemNode = itemNode.next_sibling(); \
              valueClassName* secondloaderObject = (valueClassName*) ClassFactory::CreateInstance(wxString(itemNode.name(),wxConvUTF8));   \
              valueClassName* secondObject = (valueClassName*) secondloaderObject->Load(itemNode, resetMode); \
              delete secondloaderObject; \
              if(!resetMode) { \
                  hashClassName::value_type val(firstObject, secondObject); \
                  instance->attributeArg->insert(val); \
              } \
              itemNode = itemNode.next_sibling(); \
            } \
        } else { \
        } \
        listNode = listNode.next_sibling();  \
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


#define END_LOAD(index, className) \
        return instance; \
    }


#endif // XMLGAMEMACROS_H
