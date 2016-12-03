#include "pileupeffect.h"

PileUpEffect::PileUpEffect()
{
}

const float SPEED = 1080 / 0.3f;

int PileUpEffect::acceptsString(const InputString &inputString)
{
    return inputString.startsWith(8, SOT_WORD) ? 30 : 0;
}

void PileUpEffect::transform(Text &t, float &time, Node &inputNode,
                             glm::vec3 startPos, glm::vec3 startRot,
                             glm::vec3 endPos, glm::vec3 endRot,
                             glm::vec3 scPos, glm::vec3 scRot)
{
    t.setPosition(startPos);
    t.setRotation(startRot);

    // Move/Rotate next to
    glm::vec3 delta = endPos - startPos;
    float dur = glm::length(delta) / SPEED;
    //float dur = 0.4;
    t.runAction(time, new MoveBy(dur, delta));
    t.runAction(time, new RotateTo(dur, endRot.x, endRot.y, endRot.z));
    time += dur;

    // Move/rotate scene
    dur = 0.3f;
    inputNode.runAction(time, new MoveTo(dur, scPos));
    inputNode.runAction(time, new RotateTo(dur, scRot.x, scRot.y, scRot.z));
    time += dur;
}

Text* PileUpEffect::newText(InputString &inputString,
                            Node &inputNode, float width, float maxHeight, Point &td)
{
    auto t = new Text(toUpper(inputString.read(1, SOT_WORD)), "Roboto-Bold");
    inputNode.addChild(t);
    t->setLineLength(1000000);
    t->setScaleForWidth(width);
    td = t->getDimensions();
    if (td.y > maxHeight) {
        t->setScaleForHeight(maxHeight);
        t->setLineLength(width);
        t->setAlignment(ALIGN_RIGHT);
        td = t->getDimensions();
        td.x = width;
    }
    return t;
}

Text* PileUpEffect::newTextWithHeight(InputString &inputString,
                            Node &inputNode, float height, Point &td)
{
    auto t = new Text(toUpper(inputString.read(1, SOT_WORD)), "Roboto-Bold");
    inputNode.addChild(t);
    t->setLineLength(1000000);
    t->setScaleForHeight(height);
    td = t->getDimensions();
    return t;
}


float PileUpEffect::run(InputString &inputString, Node &inputNode, float startTime)
{
    //               +-----+
    //      +----+   |     |
    //  +---+    |   |     |
    //  |   |    +---+     |
    //  |   |    |   |     |
    //  |t5 | t5 |t5 | t5  |
    //  |   |    |   |     |
    //  +---+----+------+--+
    //  |     t      |  |  |
    //  +------------+t3|t4|
    //  |     t2     |  |  |
    //  +------------+--+--+

    float space = 30;
    float maxTextHeight = 800;

    inputNode.runAction(startTime,
        new MoveTo(0, glm::vec3(0, 0, 0))
    );

    float baseWidth = 1000;
    float trDur = 0.3;

    // Create new word
    Point td;
    auto t = newText(inputString, inputNode, baseWidth, maxTextHeight, td);
    t->setAlpha(0);
    glm::vec3 tp(1920 - baseWidth, 0, -600);
    t->setPosition(tp);

    // Fly to the scene
    t->runAction(startTime, new FadeIn(0.1));
    tp = {(1920 - baseWidth) / 2, (1080 - td.y) / 2, 0};
    t->runAction(startTime, new EaseIt(
        new MoveTo(trDur, tp)
    ));
    startTime += trDur;

    // ================

    Point t2d;
    Text *t2 = newText(inputString, inputNode, baseWidth, maxTextHeight, t2d);
    glm::vec3 t2p(tp.x, tp.y - space - t2d.y, 0);
    transform(*t2, startTime, inputNode,
              glm::vec3(tp.x, -t2d.y, 0), glm::vec3(0,0,0),
              t2p, glm::vec3(0,0,0),
              glm::vec3(0, (td.y + t2d.y) / 2 + space, 0), glm::vec3(0,0,0));

    Point t3d;
    Text *t3 = newText(inputString, inputNode, td.y + space + t2d.y, maxTextHeight, t3d);
    glm::vec3 t3p(tp.x+td.x+space+t3d.y, t2p.y, 0);
    transform(*t3, startTime, inputNode,
              glm::vec3(1920+t3d.y, t2p.y, 0), glm::vec3(0,0,-90),
              t3p, glm::vec3(0,0,-90),
              glm::vec3(-t2p.y + (1920 - t3d.x) / 2, t3p.x + (1080 - t3d.y) / 2, 0), glm::vec3(0,0, 90));

    Point t4d;
    Text *t4 = newText(inputString, inputNode, t3d.x, maxTextHeight, t4d);
    glm::vec3 t4p(t3p.x+space+t4d.y, t3p.y, 0);
    transform(*t4, startTime, inputNode,
              glm::vec3(t3p.x+1080/2+t4d.y, t4p.y, 0), glm::vec3(0,0,-90),
              t4p, glm::vec3(0,0,-90),
              glm::vec3(-t3p.y + (1920 - t4d.x) / 2, t4p.x + (1080 - t4d.y) / 2, 0), glm::vec3(0,0, 90));

    // Right column
    float lineHeight = (td.x + 4*space + t3d.y + t4d.y) / 4 - space;

    float zoomStartTime = startTime;

    startTime += 0.3f;

    float maxWidth = 0;
    for (int i = 0; i < 4; ++i) {
        Point t5d;
        Text *t5 = newTextWithHeight(inputString, inputNode, lineHeight, t5d);
        if (t5d.x > maxWidth)
            maxWidth = t5d.x;
        glm::vec3 t5p(tp.x+t5d.y+i*lineHeight, tp.y+td.y+space, 0);
        t5->setRotation(glm::vec3(0,0,-90));
        t5->setPosition(t5p.x, t3p.y+(t3d.x+9000)/2, 0);

        t5->runAction(startTime, new MoveTo(0.15f, t5p));
        startTime += 0.15;
        if (i == 0) {
            t2->runAction(startTime, new MoveBy(0.2, glm::vec3(0, -2500, 0)));
        } else if (i == 1) {
            t->runAction(startTime, new MoveBy(0.2, glm::vec3(0, -2500, 0)));
        } else if (i == 2) {
            t3->runAction(startTime, new MoveBy(0.2, glm::vec3(0, -2500, 0)));
        } else if (i == 3) {
            t4->runAction(startTime, new MoveBy(0.2, glm::vec3(0, -2500, 0)));
        }
        startTime += 0.2;
    }

    float totalWidth = t2d.y + tp.y + maxWidth + 2*space + 250;
    float widthScale = 1920 / totalWidth;
    float totalHeight = t2d.x + t3d.y + t4d.y + 2*space + 250;
    float heightScale = 1080 / totalHeight;
    float finalScale = glm::min(widthScale, heightScale);

    glm::vec3 pivot(tp.x+125+totalHeight/2, t2p.y+125+totalWidth/2, 0);
    inputNode.runAction(zoomStartTime, new MoveTo(0.3f, glm::vec3(
        -t2p.y+(1920-totalWidth)/2+(1-finalScale)*pivot.y,
        t2p.x+totalHeight+(1080-totalHeight)/2-(1-finalScale)*pivot.x,
        0
    )));


    inputNode.runAction(zoomStartTime, new ScaleTo(0.3f, finalScale));

//    inputNode.runAction(zoomStartTime, new Sequence(
//        new CallFunction([&inputNode, pivot]{
//            inputNode.setAnchorPoint(pivot.x/1920, pivot.y/1080);
//        }),
//        new ScaleTo(0.3f, finalScale*finalScale),
//        nullptr
//    ));

    // Clean everything

    startTime += 0.3;

    inputNode.runAction(startTime,
        new MoveTo(0, glm::vec3(-1920, 0, 0))
    );

    return startTime;
}
