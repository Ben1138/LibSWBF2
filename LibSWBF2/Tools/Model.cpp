#include "stdafx.h"
#include "Level.h"
#include "Logging\Logger.h"

namespace LibSWBF2::Tools
{
	using Logging::ELogType;

	Model::Model(modl* modelChunk)
	{
		p_Model = modelChunk;
	}

	Model::~Model()
	{
		for (size_t i = 0; i < m_Segments.Size(); ++i)
		{
			Segment::Destroy(m_Segments[i]);
		}
		m_Segments.Clear();
	}

	Model* Model::FromChunk(Level* mainContainer, modl* modelChunk)
	{
		if (mainContainer == nullptr)
		{
			LOG("Given mainContainer was NULL!", ELogType::Error);
			return nullptr;
		}
		if (modelChunk == nullptr)
		{
			LOG("Given modelChunk was NULL!", ELogType::Error);
			return nullptr;
		}

		Model* result = new Model(modelChunk);
		return result;
	}

	void Model::Destroy(Model* model)
	{
		if (model == nullptr)
		{
			LOG("Given model was NULL!", ELogType::Error);
			return;
		}

		delete model;
	}

	String Model::GetName() const
	{
		return p_Model->p_Name->m_Text;
	}

	const List<Segment*>& Model::GetSegments() const
	{
		return m_Segments;
	}
}