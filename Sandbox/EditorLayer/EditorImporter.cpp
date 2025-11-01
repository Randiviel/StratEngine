#include "EditorImporter.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace Editor
{
    void Importer::ImportObject(StratEngine::Scene* scene, const char* filePath)
    {
        if(scene == nullptr || filePath == nullptr || filePath[0] == '\0') 
        {
            STRAT_CLIENT_ERROR("While importing files the Scene or FilePath is nullptr");
            return;
        }


        Assimp::Importer importer;
        
        const aiScene* iScene = importer.ReadFile(filePath, 
                aiProcess_Triangulate |   
                aiProcess_FlipUVs   |         
                aiProcess_GenNormals |     
                aiProcess_PreTransformVertices |
                aiProcess_GlobalScale |
                aiProcess_CalcTangentSpace);


        if(iScene == nullptr)
        {
            STRAT_CLIENT_ERROR("FilePath is wrong! Couldn't read file! FilePath: {0}", filePath);
            return;
        }

        // ProcessNode(scene, iScene->mRootNode, iScene, glm::mat4(1.0f));
        for(unsigned int i = 0; i < iScene->mNumMeshes; i++)
        {
            aiMesh* mesh = iScene->mMeshes[i];
            std::vector<float> vertices;
            
            for(unsigned int v = 0; v < mesh->mNumVertices; v++)
            {
                vertices.push_back(mesh->mVertices[v].x);
                vertices.push_back(mesh->mVertices[v].y);
                vertices.push_back(mesh->mVertices[v].z);
                vertices.push_back(mesh->mNormals[v].x);
                vertices.push_back(mesh->mNormals[v].y);
                vertices.push_back(mesh->mNormals[v].z);  
                if(mesh->mTextureCoords[0] != nullptr)
                {
                    vertices.push_back(mesh->mTextureCoords[0][v].x);
                    vertices.push_back(mesh->mTextureCoords[0][v].y);
                }
                else
                {
                    vertices.push_back(0.0f);
                    vertices.push_back(0.0f);
                }
            }


            auto Entity = scene->CreateEntity(mesh->mName.C_Str());
            Entity.AddComponent<StratEngine::MeshComponent>(vertices);
            Entity.AddComponent<StratEngine::TransformComponent>();
        }
    }
}
