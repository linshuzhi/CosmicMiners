//
//  UITools.cpp
//  CosmicMiners
//
//  Created by LinShulong on 15/12/18.
//
//

#include "UITools.h"
USING_NS_CC;
namespace UITools {
    cocos2d::Sprite* MakeSpiteGray(cocos2d::Sprite* ChangeSprite)
    {
        Sprite* sprite_chess = Sprite::createWithSpriteFrame(ChangeSprite->getSpriteFrame());
        sprite_chess->setPosition(sprite_chess->getContentSize().width/2, sprite_chess->getContentSize().height/2);
        
        RenderTexture *render = RenderTexture::create(sprite_chess->getContentSize().width, sprite_chess->getContentSize().height,Texture2D::PixelFormat::RGBA8888);
        render->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
        sprite_chess->visit();
        render->end();
        Director::getInstance()->getRenderer()->render();
        
        Image *finalImage = render->newImage();
        
        unsigned char *pData = finalImage->getData();
        
        int iIndex = 0;
        
        for (int i = 0; i < finalImage->getHeight(); i ++)
        {
            for (int j = 0; j < finalImage->getWidth(); j ++)
            {
                // gray
                int iBPos = iIndex;
                
                unsigned int iB = pData[iIndex];
                
                iIndex ++;
                
                unsigned int iG = pData[iIndex];
                
                iIndex ++;
                
                unsigned int iR = pData[iIndex];
                
                iIndex ++;
                iIndex ++;
                
                unsigned int iGray = 0.3 * iR + 0.6 * iG + 0.1 * iB;
                
                pData[iBPos] = pData[iBPos + 1] = pData[iBPos + 2] = (unsigned char)iGray;
            }
            
        }
        
        
        Texture2D *texture = new Texture2D;
        
        texture->initWithImage(finalImage);
        
        auto pSprite = Sprite::createWithTexture(texture);
        
        delete finalImage;
        
        texture->release();
        
        return pSprite;
        
    }
}