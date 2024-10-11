import torch
from transformers import BertTokenizer, BertModel

from sentence_transformers import SentenceTransformer
from sklearn.metrics.pairwise import cosine_similarity

import numpy as np

from transformers import MarianMTModel, MarianTokenizer
from googletrans import Translator

tokenizer = BertTokenizer.from_pretrained('bert-base-uncased')
model = BertModel.from_pretrained('bert-base-uncased')

def get_embeddings(text):
    inputs = tokenizer(text, return_tensors='pt', truncation=True, padding=True)
    outputs = model(**inputs)
    return outputs.last_hidden_state.mean(dim=1).detach()

def compute_sim_matrix(paragraph):
    for i in range(0,len(paragraph)):
        paragraph1 = paragraph[i]
        embeddings1 = get_embeddings(paragraph1)

        if (i==0) :
            print(embeddings1.shape, np.dot(embeddings1[i], embeddings1[i]))

        print(i, " : ")
        for j in range(0, len(paragraph)):
            paragraph2 = paragraph[j]
            embeddings2 = get_embeddings(paragraph2)

            cosine_sim = torch.nn.functional.cosine_similarity(embeddings1, embeddings2)
            print(f"{cosine_sim.item()} ")

def compute_sim_matrix_sbert(paragraph):
    model = SentenceTransformer('paraphrase-MiniLM-L6-v2')
    #paragraphs = ["This is the first paragraph.", "This is the second paragraph."]

    # Convert paragraphs into embeddings
    embeddings = model.encode(paragraph)
    print("data size=", len(embeddings))

    unit_embeddings = embeddings
    for i in range(0,len(embeddings)):
        unit_embeddings[i] = embeddings[i]/np.linalg.norm(embeddings[i])

    # Calculate cosine similarity
    #similarity = cosine_similarity([embeddings[20]], [embeddings[21]])
    #print(type(embeddings[0]), embeddings[0].shape, np.dot(embeddings[0], embeddings[0]))
    #print("length=", embeddings[0])
    #print(f"Similarity: {similarity[0][0]}")

    for i in range(0,len(paragraph)):
        print(i, " : ")
        for j in range(0, len(paragraph)):
            cos_sim = np.dot(unit_embeddings[i], unit_embeddings[j])
            dist = np.dot(embeddings[i], embeddings[i]) - 2.0*np.dot(embeddings[i], embeddings[j]) + np.dot(embeddings[j], embeddings[j]) #cosine_similarity(embeddings[i], embeddings[j])
            print(f"{cos_sim}, {dist} ")


paragraph = []
paragraph.append("미래 도시의 3D 모델을 설계합니다. 고층 빌딩, 공원, 다리, 다양한 교통수단(예: 하늘을 나는 자동차, 지하철 등)을 포함하고 날씨 효과, 낮과 밤의 변화, 사람들이 움직이는 모습을 추가하여 도시환경을 표현합니다.")
paragraph.append("다양한 행동(걷기, 뛰기, 점프 등)을 수행하는 캐릭터를 설계하고 애니메이션으로 표현합니다. 캐릭터의 표정과 몸짓을 통해 감정을 미세하게 표현하고, 소품이나 환경을 추가해 맥락을 부여합니다")
paragraph.append("마야를 사용해 고품질의 사진처럼 사실적인 자동차를 모델링하고 렌더링합니다. 내부 디자인, 조명, 반사 표면 및 텍스처와 같은 세부 사항을 추가하고, 현실적인 환경에 자동차를 통합하여 시각적 매력 추가합니다")
paragraph.append("가상 현실 경험을 위한 몰입감 있는 3D 환경을 설계 및 모델링 합니다. 이 장면은 숲, 외계 행성 또는 수중 세계일 수 있으며 성능을 최적화하고 원활한 폴리곤 수와 상호작용 요소를 포함해 VR에 적합한 모델을 제작해야 합니다")
paragraph.append("간단한 스토리가 있는 1~2분 길이의 CG 단편 영화를 제작합니다. 캐릭터 애니메이션, 간단한 줄거리, 사운드 디자인 및 후반 제작 효과를 포함하며. 성우 및 음향 효과는 다른 사람과 협업할 수 있습니다")
paragraph.append("ZBrush 또는 유사한 프로그램을 사용해 판타지 생명체(예: 드래곤, 신화적 생명체) 조각을 세밀하게 모델링합니다. 해부학, 텍스처 및 비늘, 털, 근육 등의 세부 표현이 되어야 하며. 최종 결과물은 고해상도 정적 모델이어야 합니다")
paragraph.append("선택한 곡에 맞춰 모션 그래픽 시퀀스를 제작합니다. 애니메이션된 타이포그래피, 추상적인 형상 및 동적 전환을 사용해 리듬과 곡의 분위기를 시각적으로 향상시킬 수 있어야 합니다")
paragraph.append("Unity 또는 Unreal Engine과 같은 게임 엔진을 위한 완전한 기능의 3D 에셋(무기, 차량, 캐릭터 등)을 설계합니다. 에셋에는 세밀한 텍스처, 애니메이션 및 물리 기반 상호작용을 포함해야 합니다")
paragraph.append("폭발, 마법, 날씨 효과를 실사 영상에 추가합니다. 조명, 움직임, 카메라 각도를 맞춰 CG 요소를 영상에 자연스럽게 융합시키는 것이 과제입니다")
paragraph.append("사실적인 건축 내부 또는 외부(주택, 사무실, 공공 장소 포함)를 설계합니다. 가구, 조명, 장식 등의 세부 사항을 추가하고 건축 프레젠테이션에 사용할 수 있는 포토리얼 렌더를 목표로 합니다")
paragraph.append("실제 제품(예: 스마트폰, 자동차, 가전제품 등)의 3D 모델을 제작하고, 제품의 기능을 강조하는 짧은 광고 영상도 제작합니다. 제품이 회전하거나 분해되어 내부 구조를 보여주는 등 다양한 연출을 추가되어야 합니다")
paragraph.append("폭풍우, 화산 폭발, 지진, 파도 등의 자연 현상을 CG로 시뮬레이션합니다. 자연스러운 물리적 움직임과 사실적인 텍스처를 강조하여 환경과 상호작용하는 자연현상을 표현합니다")
paragraph.append("공상과학 소설에 나올 법한 복잡한 로봇을 디자인합니다. 로봇의 기계적 부분, 합금 텍스처, 내부 구조 등을 포함한 디테일을 강조하고, 움직일 수 있도록 리깅합니다")
paragraph.append("AR 앱이나 게임을 위한 3D 인터페이스를 설계합니다. 사용자가 실제 환경에서 상호작용할 수 있는 UI 요소와 물체를 포함하여, AR 기술과의 상호작용이 원활하도록 디자인 되어야 합니다")
paragraph.append("동물의 털이나 인간의 머리카락을 사실적으로 시뮬레이션합니다. 털의 움직임과 빛 반사, 자연스러운 물리적 특성 등을 살려 캐릭터 또는 동물 모델에 통합합니다")
paragraph.append("미래의 공공시설(예: 공항, 기차역, 병원 등)을 주제로 3D 환경을 디자인합니다. 첨단 기술과 혁신적인 디자인 요소를 반영하여 미래적인 건축물을 설계하고, 사람들이 이용하는 장면을 애니메이션으로 표현합니다")
paragraph.append("독창적인 타이포그래피 애니메이션을 제작합니다. 텍스트가 움직이거나 변형되는 방식으로 메시지를 전달하는 창의적인 시퀀스를 설계하고, 색상과 타이밍을 적절하게 조정하여 시각적 효과를 극대화합니다")
paragraph.append("의류 또는 액세서리 컬렉션을 3D로 모델링하고 애니메이션으로 표현하세요. 소재의 질감과 움직임을 자연스럽게 시뮬레이션하여 패션 제품을 가상 런웨이에서 선보이는 시퀀스를 제작하세요")
paragraph.append("다양한 감정을 표현하는 캐릭터 얼굴 표정 애니메이션을 제작하세요. 기쁨, 슬픔, 분노 등 여러 감정을 미세하게 조정된 표정으로 나타내며, 캐릭터의 눈, 입, 얼굴 근육이 자연스럽게 움직이도록 설정하세요")
paragraph.append("색상과 형태를 기반으로 한 추상적인 3D 애니메이션을 제작하세요. 추상적인 패턴, 입자 효과, 형상의 변형 등을 사용하여 예술적이고 감각적인 시퀀스를 만드세요. 이 프로젝트는 주로 예술적 감각과 창의성을 요구합니다")
paragraph.append("I like to play tennis") #"나는 테니스를 좋아합니다")
paragraph.append("I am doing activity sports in my free time") #나는 시간 날때마다 운동을 합니다")

en_paragraph = []
en_paragraph.append("Design 3D models of future cities. It represents an urban environment by including skyscrapers, parks, bridges, and various modes of transportation (e.g. flying cars, subways, etc.) and adding weather effects, day and night changes, and people moving around")
en_paragraph.append("Design and animate characters performing various actions (walking, running, jumping, etc.). Emotions are subtly expressed through the character's facial expressions and gestures, and context is given by adding props or environments")
en_paragraph.append("Model and render high-quality, photorealistic cars using Maya. Add details such as interior design, lighting, reflective surfaces and textures, and integrate the car into a realistic environment to add visual appeal")
en_paragraph.append("Design and model immersive 3D environments for virtual reality experiences. This scene could be a forest, an alien planet, or an underwater world, and you need to create a VR-ready model that optimizes performance and includes smooth polygon counts and interactive elements")
en_paragraph.append("Create a 1-2 minute long CG short film with a simple story. Includes character animation, brief plot, sound design, and post-production effects. Voice actors and sound effects can collaborate with others")
en_paragraph.append("Model pieces of fantasy creatures (e.g. dragons, mythical creatures) in detail using ZBrush or a similar program. Anatomy, texture, scales, fur, muscles, etc. must be expressed in detail. The final result should be a high-resolution static model")
en_paragraph.append("Create a motion graphics sequence to match your chosen song. You should be able to visually enhance the rhythm and mood of the song using animated typography, abstract shapes, and dynamic transitions")
en_paragraph.append("Design fully functional 3D assets (weapons, vehicles, characters, etc.) for game engines like Unity or Unreal Engine. Assets should include detailed textures, animations, and physically-based interactions")
en_paragraph.append("Add explosions, magic, and weather effects to your live-action videos. The challenge is to naturally integrate CG elements into the video by matching lighting, movement, and camera angles")
en_paragraph.append("Design realistic architectural interiors or exteriors, including homes, offices, and public spaces. The goal is to create photorealistic renders that can be used in architectural presentations, adding details such as furniture, lighting, and decoration")
en_paragraph.append("We create 3D models of real products (e.g. smartphones, cars, home appliances, etc.) and also create short advertising videos that highlight the features of the products. Various presentations should be added, such as rotating or disassembling the product to show the internal structure")
en_paragraph.append("Natural phenomena such as storms, volcanic eruptions, earthquakes, and waves are simulated using CG. Expresses natural phenomena interacting with the environment by emphasizing natural physical movement and realistic textures")
en_paragraph.append("Design complex robots straight out of science fiction. Highlight details, including the robot's mechanical parts, alloy textures, and internal structures, and rig it for movement")
en_paragraph.append("Design 3D interfaces for AR apps or games. Interaction with AR technology should be designed to be seamless, including UI elements and objects that users can interact with in the real environment")
en_paragraph.append("Realistic simulation of animal fur or human hair. Integrate fur movement, light reflection, and natural physical characteristics into character or animal models")
en_paragraph.append("Design 3D environments for future public facilities (e.g. airports, train stations, hospitals, etc.). We design futuristic buildings by reflecting cutting-edge technology and innovative design elements, and depict scenes of people using them through animation")
en_paragraph.append("We create original typography animations. Design creative sequences that convey your message by moving or transforming text, and adjust color and timing to maximize visual impact")
en_paragraph.append("Model and animate your clothing or accessory collection in 3D. Create sequences that showcase fashion products on a virtual runway by naturally simulating the texture and movement of materials")
en_paragraph.append("Create character facial expression animations that express various emotions. Express various emotions such as joy, sadness, anger, and more with finely tuned facial expressions, and set your character's eyes, mouth, and facial muscles to move naturally")
en_paragraph.append("Create abstract 3D animations based on color and shape. Create artistic and sensational sequences using abstract patterns, particle effects, shape transformations, and more. This project mainly requires artistic flair and creativity")


titles = []
titles.append("미래 도시 모델링")
titles.append("캐릭터 애니메이션")
titles.append("실제와 같은 자동차 렌더링")
titles.append("가상현실 환경 모델링")
titles.append("애니메이션 단편 영화")
titles.append("판타지 생명체 디지털 조각")
titles.append("뮤직비디오용 모션 그래픽")
titles.append("실시간 상호작용 게임 에셋")
titles.append("시각효과 장면 통합")
titles.append("건축 시각화")
titles.append("제품 광고용 3D 모델링 및 애니메이션")
titles.append("자연현상 CG 시뮬레이션")
titles.append("공상고학 로봇 디자인")
titles.append("증강현실 인터페이스 디자인")
titles.append("생명체 털 및 머리카락 시뮬레이션")
titles.append("미래 도시 공공 시설 시각화")
titles.append("타이포그래피 애니메이션")
titles.append("디지털 패션 디자인")
titles.append("캐릭터 얼굴 표정 애니메이션")
titles.append("추상 미술 애니메이션")

en_titles=[]
en_titles.append("future city modeling")
en_titles.append("character animation")
en_titles.append("Realistic car rendering")
en_titles.append("Virtual reality (VR) environment modeling")
en_titles.append("animated short film")
en_titles.append("fantasy creature digital sculpture")
en_titles.append("Motion graphics for music videos")
en_titles.append("Real-time interactive game assets")
en_titles.append("Visual effects (VFX) scene integration")
en_titles.append("architectural visualization")
en_titles.append("3D modeling and animation for product advertising")
en_titles.append("Natural phenomenon CG simulation")
en_titles.append("science fiction robot design")
en_titles.append("AR interface design")
en_titles.append("Creature fur and hair simulation")
en_titles.append("Visualization of future city public facilities")
en_titles.append("typography animation")
en_titles.append("digital fashion design")
en_titles.append("Character facial expression animation")
en_titles.append("abstract art animation")

en_skill = []
en_skill.append("3D modeling, lighting, texturing")
en_skill.append("Rigging, character animation, motion capture")
en_skill.append("Photo-realistic rendering, surface modeling, material texturing")
en_skill.append("VR, optimization, environment design, interaction design")
en_skill.append("Storyboarding, animation, compositing, sound design")
en_skill.append("Digital sculpting, texturing, anatomy")
en_skill.append("Motion graphics, after effects, animation synchronization")
en_skill.append("Game development, asset design, rigging, texturing")
en_skill.append("VFX, compositing, tracking, lighting integration")
en_skill.append("Architectural modeling, rendering, lighting design, texturing")
en_skill.append("Product modeling, animation, camera work, rendering")
en_skill.append("Simulation, physically-based rendering, texturing")
en_skill.append("Robot design, rigging, texturing, animation")
en_skill.append("AR development, 3D UI/UX, interaction design")
en_skill.append("Hair simulation, physics engine, texturing")
en_skill.append("Architectural visualization, animation, environmental design")
en_skill.append("Typography design, motion graphics, timing coordination")
en_skill.append("3D fashion design, texturing, animation")
en_skill.append("Facial Rigging, Animation, Emotes")
en_skill.append("Animation, abstract art, color and sculptural design")

def translate_marianmt(input_text):
    translate_model_name = 'Helsinki-NLP/opus-mt-ko-en'
    translate_tokenizer = MarianTokenizer.from_pretrained(translate_model_name)
    translate_model = MarianMTModel.from_pretrained(translate_model_name)

    
    inputs = translate_tokenizer(input_text, return_tensors="pt", padding=True)

    translated = translate_model.generate(**inputs)
    translated_text = translate_tokenizer.decode(translated[0], skip_special_tokens=True)
    print(translated_text)

#translate_marianmt("자연현상 CG 시뮬레이션")

def translate_googletrans(input_text, src, dest):
    translator = Translator()
    translation = translator.translate(input_text)
    print(translation.text)

translate_googletrans("색상과 형태를 기반으로 한 추상적인 3D 애니메이션을 제작하세요. 추상적인 패턴, 입자 효과, 형상의 변형 등을 사용하여 예술적이고 감각적인 시퀀스를 만드세요. 이 프로젝트는 주로 예술적 감각과 창의성을 요구합니다", "ko", "en")

#compute_sim_matrix(paragraph)

#compute_sim_matrix_sbert(en_titles)
compute_sim_matrix_sbert(en_paragraph)
#compute_sim_matrix_sbert(en_skill)

